# Import require libraries
from cs50 import SQL
import sys

db = SQL("sqlite:///students.db")

# ----------------------------------------------------------
# Check that only 2 command line arguments have been passed
if len(sys.argv) is not 2:
    print("Usage: python roster.py House")
    exit()

h = sys.argv[1]

# ----------------------------------------------------------
# Use SQL commands to print a list of students from the student database for the selected house
# In alphabetical order by last name (then first name)
# Print full name, and birth year. Format: Harry James Potter, born 1980

list = db.execute('SELECT first, middle, last, birth FROM students WHERE house = "{}" ORDER BY last, first;'.format(h))

for row in list:
    
    # Print first name
    print(row["first"], end=" ")
    
    # Print middle name if there is one
    if row["middle"] is not None:
        print(row["middle"], end=" ")
    
    # Print last name
    print(row["last"], end=", ")
    
    # Print birth year
    print("born", row["birth"])
