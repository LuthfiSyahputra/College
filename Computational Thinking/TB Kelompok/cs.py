import csv



def cardDatabase_read(file = "cardDatabase.csv", delimiter:str = ","):
    database  = open(file, "r+", newline = "")
    database2 = open(file, "r+", newline = "")
    
    dataReader = csv.reader(database, delimiter=delimiter)
    return [[int(row[0]), str(row[1]), float(row[2]), int(row[3]), str(row[4]), float(row[5])] for row in dataReader]

cardDatabase = cardDatabase_read()

for i in range(len(cardDatabase)):
    print(cardDatabase[i])