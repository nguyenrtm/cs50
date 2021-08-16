import csv
import sys


# Open files
if len(sys.argv) != 3:
    print("Error")
csv_file = open(sys.argv[1])
csv = csv.DictReader(csv_file)
file = open(sys.argv[2])
sequences = file.read()
# Now it's the real deal
# Compute longest run of STRs
cols, rows = (len(sequences), 8)
arr = [[0] * cols for i in range(rows)]
for i in range(len(sequences)):
    AGATC = 0
    x = i
    while sequences[x:x + 5] == "AGATC":
        AGATC += 1
        x += 5
    arr[0][i] = AGATC
for i in range(len(sequences)):
    TTTTTTCT = 0
    x = i
    while sequences[x:x + 8] == "TTTTTTCT":
        TTTTTTCT += 1
        x += 8
    arr[1][i] = TTTTTTCT
for i in range(len(sequences)):
    AATG = 0
    x = i
    while sequences[x:x + 4] == "AATG":
        AATG += 1
        x += 4
    arr[2][i] = AATG
for i in range(len(sequences)):
    TCTAG = 0
    x = i
    while sequences[x:x + 5] == "TCTAG":
        TCTAG += 1
        x += 5
    arr[3][i] = TCTAG
for i in range(len(sequences)):
    GATA = 0
    x = i
    while sequences[x:x + 4] == "GATA":
        GATA += 1
        x += 4
    arr[4][i] = GATA
for i in range(len(sequences)):
    TATC = 0
    x = i
    while sequences[x:x + 4] == "TATC":
        TATC += 1
        x += 4
    arr[5][i] = TATC
for i in range(len(sequences)):
    GAAA = 0
    x = i
    while sequences[x:x + 4] == "GAAA":
        GAAA += 1
        x += 4
    arr[6][i] = GAAA
for i in range(len(sequences)):
    TCTG = 0
    x = i
    while sequences[x:x + 4] == "TCTG":
        TCTG += 1
        x += 4
    arr[7][i] = TCTG
list = {}
list['AGATC'] = max(arr[0])
list['TTTTTTCT'] = max(arr[1])
list['AATG'] = max(arr[2])
list['TCTAG'] = max(arr[3])
list['GATA'] = max(arr[4])
list['TATC'] = max(arr[5])
list['GAAA'] = max(arr[6])
list['TCTG'] = max(arr[7])
names = ["AGATC", "TTTTTTCT", "AATG", "TCTAG", "GATA", "TATC", "GAAA", "TCTG"]
# Check what STRs that need to be compared
headers = csv.fieldnames
todo = []
for i in range(len(headers)):
    for j in range(len(names)):
        if headers[i] == names[j]:
            todo.append(headers[i])
for row in csv:
    for i in range(len(todo)):
        if int(row[todo[i]]) != list[todo[i]]:
            break
    else:
        print(f"{row['name']}")
        break
else:
    print("No match")

