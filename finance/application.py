import os
import datetime

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # Get all stocks currently owned by user
    stocks = db.execute("SELECT * FROM holdings WHERE user_id = :user_id",
                        user_id=session["user_id"])

    # Use lookup to get current price of all stocks
    #prices = []
    overall_total = 0
    for row in stocks:
        result = lookup(row["symbol"])
        # Add all prices into stocks dictionary in usd format
        row["price"] = usd(result["price"])
        # Add overall value of this stock to stocks dictionary
        row["total"] = usd(result["price"] * row["shares"])
        # Calulate total value of all shares
        overall_total += row["shares"] * result["price"]

    # Get users cash balance
    cash = db.execute("SELECT cash FROM users WHERE id = :user_id",
                      user_id=session["user_id"])
    cash = cash[0]["cash"]

    # Calculate total value of stocks and cash
    overall_total += cash

    # Convert to usd formatting
    cash = usd(cash)
    overall_total = usd(overall_total)

    return render_template("index.html", stocks=stocks, cash=cash, overall_total=overall_total)


@app.route("/account", methods=["GET", "POST"])
@login_required
def account():
    """User account settings"""

    # User reached route via POST
    if request.method == "POST":

        # Update cash value
        if request.form.get("add_cash"):

            # Check input is numeric
            if not request.form.get("add_cash").isdigit():
                flash("Please only enter a numeric value.")
                return render_template("account.html")

            # Get users current cash value
            cash = db.execute("SELECT cash FROM users WHERE id = :user_id",
                              user_id=session["user_id"])

            # Update cash value
            db.execute("UPDATE users SET cash = :cash WHERE id = :user_id",
                        cash=(float(request.form.get("add_cash")) + float(cash[0]["cash"])), user_id=session["user_id"])

            flash("Cash successfully added to your account.")
            return render_template("account.html")

        # Change password
        elif request.form.get("current_pwd"):

            # Check password was submitted
            if not request.form.get("current_pwd") or not request.form.get("new_pwd") or not request.form.get("confirm_pwd") :

                flash("Please enter current password and new password.")
                return render_template("account.html")

             # Query database to get users password hash
            pwd_hash = db.execute("SELECT hash FROM users WHERE id = :user_id",
                          user_id=session["user_id"])

            # Check current password matches stored password hash
            if not check_password_hash(pwd_hash[0]["hash"], request.form.get("current_pwd")):

                flash("Invalid password.")
                return render_template("account.html")

            # Check password matches the confirmation password
            if request.form.get("new_pwd") != request.form.get("confirm_pwd"):

                flash("New passwords do not match.")
                return render_template("account.html")

            # Update passwrod in users database
            db.execute("UPDATE users SET hash = :pwd_hash WHERE id = :user_id",
                        pwd_hash=generate_password_hash(request.form.get("new_pwd")), user_id=session["user_id"])

            flash("Password sucessfully updated.")
            return render_template("account.html")

        else:
            flash("No data entered.")
            return render_template("account.html")


    #User reached route via GET
    else:

        # Get user information
        info = db.execute("SELECT * FROM users WHERE id = :user_id",
                          user_id=session["user_id"])
        cash = usd(info[0]["cash"])
        username = info[0]["username"]

        # Render account.html with users information
        return render_template("account.html", cash=cash, username=username)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    # User reached route via POST
    if request.method == "POST":

        # Check symbol was submitted
        if not request.form.get("symbol"):
            return apology("Please provide a symbol.")

        # Check shares values was submitted
        if not request.form.get("shares"):
            return apology("Please provide a number of shares.")

        # Check number of shares is a +ve int
        try:
            if int(request.form.get("shares")) <= 0:
                return apology("Please provide a number of shares greater than zero.")
        # If try fails then a folat was entered
        except:
            return apology("Please provide a whole number of shares.")

        # Use lookup() function
        order = lookup(request.form.get("symbol"))

        # Check symbol is valid
        if order == None:
            return apology("Symbol not found. Please try again.")

        # Get users cash value
        cash = db.execute("SELECT cash FROM users WHERE id = :user_id",
                          user_id=session["user_id"])
        cash = cash[0]["cash"]

        # Calculate total cost of buy request
        total_cost = int(request.form.get("shares")) * float(order["price"])

        # Check user has enough cash to buy
        if cash < total_cost:
            return apology("Not enough cash to complete this transaction.")

        # Add new line to trade history database
        db.execute("INSERT INTO history (user_id, symbol, company_name, shares, purchase_price_per_share, buy_sell, datestamp) VALUES (:user_id, :symbol, :company_name, :shares, :price, :buy_sell, :datestamp)",
                    user_id=session["user_id"], symbol=order["symbol"], company_name=order["name"], shares=request.form.get("shares"), price=order["price"], buy_sell="buy", datestamp=datetime.datetime.now())

        # Update holdings database
        # Check if user already owns shared from this company
        existing = db.execute("SELECT * FROM holdings WHERE user_id = :user_id AND symbol = :symbol",
                               user_id=session["user_id"], symbol=order["symbol"])

        if len(existing) == 0:
            db.execute("INSERT INTO holdings (user_id, symbol, company_name, shares) VALUES (:user_id, :symbol, :company_name, :shares)",
                        user_id=session["user_id"], symbol=order["symbol"], company_name=order["name"], shares=request.form.get("shares"))

        else:
            db.execute("UPDATE holdings SET shares = :shares WHERE user_id = :user_id AND symbol = :symbol",
                        shares=(existing[0]["shares"] + int(request.form.get("shares"))), user_id=session["user_id"], symbol=order["symbol"])

        # Update users cash balance
        db.execute("UPDATE users SET cash = :cash WHERE id = :user_id",
                    cash=(cash - total_cost), user_id=session["user_id"])


        flash("Purchase successful.")
        return redirect("/")

    # User reached route via GET
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    # Get transation history from hsitory database for this user
    history = db.execute("SELECT * FROM history WHERE user_id = :user_id",
                         user_id=session["user_id"])

    # Render history.html and pass required history data.
    return render_template("history.html", history=history)



@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    # User reached route via POST
    if request.method == "POST":

        # Use lookup function to find
        quote = lookup(request.form.get("symbol"))

        # If no result found
        if quote == None:
            flash("No result found.")
            return redirect("/quote")

        # Render quoted.html
        return render_template("quoted.html", quote=quote)

    # User reached route via GET
    else:
        # Render quote.html
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # User reached route via POST
    if request.method == "POST":

        # Check username was submitted and if it already exists
        if not request.form.get("username"):
            return apology("Please provide a username")

        # Check username doesn't already exist
        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))
        if len(rows) != 0:
            return apology("Username already exists.")

        # Check password was submitted
        if not request.form.get("password"):
            return apology("Please provide a password.")

        # Check password matches the confirmation password
        if request.form.get("password") != request.form.get("confirmation"):
            return apology("Passwords do not match.")

        # Insert new user into user database
        pkey = db.execute("INSERT INTO users (username, hash) VALUES (:username, :pwdhash)",
                          username=request.form.get("username"), pwdhash=generate_password_hash(request.form.get("password")))

        flash("You have successfully registered. Please log in.")
        return redirect("/login")

    # User reached route via GET
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    # User reached this route via POST
    if request.method == "POST":

        # Check if a stock symbol is not selected
        if not request.form.get("symbol"):
            return apology("No symbol selected.")

        # Check the user owns share in this company
        stocks = db.execute("SELECT * FROM holdings WHERE user_id = :user_id AND symbol = :symbol",
                        user_id=session["user_id"], symbol=request.form.get("symbol"))
        if len(stocks) != 1:
            return apology("You do not own shares in this company.")

        # Check that a number of shares to be sold was submitted
        if not request.form.get("shares"):
            return apology("Please select a number of shares to be sold.")

        # Check if number of shares to be sold is a positive number
        try:
            if int(request.form.get("shares")) <= 0:
                return apology("Please select a number of shares greater than zero.")
        # If try fails then a float was entered
        except:
             return apology("Please select a whole number of shares.")

        # Check if number of shares to be sold is less than or equal to the total number of shares owned
        if int(request.form.get("shares")) > int(stocks[0]["shares"]):
            return apology("You do not own this many shares.")

        # Use lookup function to find sale price
        sale = lookup(request.form.get("symbol"))

        # Sell shares in select company
        # Add new line to trade history database
        db.execute("INSERT INTO history (user_id, symbol, company_name, shares, purchase_price_per_share, buy_sell, datestamp) VALUES (:user_id, :symbol, :company_name, :shares, :price, :buy_sell, :datestamp)",
                    user_id=session["user_id"], symbol=request.form.get("symbol"), company_name=stocks[0]["company_name"], shares=request.form.get("shares"), price=sale["price"], buy_sell="sell", datestamp=datetime.datetime.now())

        # Update holdings database
        # Check if user has sold all their shares in this company
        if int(request.form.get("shares")) == stocks[0]["shares"]:

            # Remove item from holdings database
            db.execute("DELETE FROM holdings WHERE id = :id",
                        id=stocks[0]["ID"])

        # If not all shares have been sold update the shares values in the holdings database
        else:
            db.execute("UPDATE holdings SET shares = :shares WHERE id = :id",
                        shares=(int(stocks[0]["shares"]) - int(request.form.get("shares"))), id=stocks[0]["ID"])

        # Get cash value
        cash = db.execute("SELECT cash FROM users WHERE id = :user_id",
                    user_id=session["user_id"])

        # Update cash value
        db.execute("UPDATE users SET cash = :cash WHERE id = :user_id",
                    cash=(float(cash[0]["cash"]) + (int(request.form.get("shares")) * float(sale["price"]))), user_id=session["user_id"])

        flash("Shares successfully sold.")
        return redirect("/")

    # User reached this route via GET
    else:

        # Get list of all stocks currently owned by user
        stocks = db.execute("SELECT * FROM holdings WHERE user_id = :user_id",
                        user_id=session["user_id"])

        # Select just the symbol data
        #for row in stocks:
         #   del row["name"]
          #  del row["company"]

        return render_template("sell.html", symbols=stocks)

def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
