# TODO
from cs50 import SQL
import sys
import csv
import cs50


# check number of command line arguments
if len(sys.argv) != 2:
    print("Error")

# db files
db = SQL("sqlite:///students.db")

# import from csv file to database
with open(sys.argv[1]) as csv_file:
    csv = csv.DictReader(csv_file)
    for row in csv:
        names = row["name"].split(" ")
        if len(names) == 3:
            db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES (?, ?, ?, ?, ?)", 
                       names[0], names[1], names[2], row["house"], row["birth"])
        elif len(names) == 2:
            db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES (?, ?, ?, ?, ?)", 
                       names[0], None, names[1], row["house"], row["birth"])
