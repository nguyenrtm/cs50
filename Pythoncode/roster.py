# TODO
from cs50 import SQL
import sys

db = SQL("sqlite:///students.db")

if len(sys.argv) != 2:
    print("Error")
    sys.exit(1)
output = db.execute(f"SELECT first, middle, last, birth FROM students WHERE house='{sys.argv[1]}' ORDER BY last, first")
for a in output:
    if a['middle'] != None:
        print(f"{a['first']} {a['middle']} {a['last']}, born {a['birth']}")
    else:
        print(f"{a['first']} {a['last']}, born {a['birth']}")

