# Import require libraries
from cs50 import SQL
import sys
import csv

db = SQL("sqlite:///students.db")

# ----------------------------------------------------------
# Check that only 2 command line arguments have been passed
if len(sys.argv) is not 2:
    print("Usage: python import.py characters.csv")
    exit()

# ----------------------------------------------------------
# Insert CSV data into the student database
# Open csv file
with open(sys.argv[1], "r") as characters:

    # Create a dictionary reader
    reader = csv.DictReader(characters)

    # Iterate over the csv file
    for row in reader:

        # Set current row values as 3 variables
        name = row["name"].split(' ')
        house = row["house"]
        birth = row["birth"]

        # Split name into first, middle and last
        # No middle name = NULL
        if len(name) == 2:

            first = name[0]
            middle = None
            last = name[1]

        elif len(name) == 3:

            first = name[0]
            middle = name[1]
            last = name[2]

        else:
            print("Unexpected name formated")
            exit()

        # Add names to the student database
        db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)",
                first, middle, last, house, birth)