#import
import sys
import csv

#-------------------------------------------------------
#Confirm that correct command line aguments were given
#use sys.argv
if len(sys.argv) is not 3:
    print("Usage: python dna.py data.csv sequence.txt")
    exit()

#Get cvs and txt file names
csvFilename = sys.argv[1]
txtFilename = sys.argv[2]

#---------------------------------------------------------
#Open csv file
#use csv reader and DictReader
db = csv.reader(open(csvFilename))
database = []

for row in db:
    database.append(row)

#----------------------------------------------------------
#Open text file
#Use open(filename)
#Use f.read()
seq = open(txtFilename, 'r')
sequence = ''

for x in seq:
    sequence += x

#----------------------------------------------------------
#Calculate the number of back to back STRs in the sequence

#Declare variables
#Count is a list of the back to back STRs (in the same order as listed in database)
count = [0 for i in database[0]]
#posSTR tracks the position of the current STR
posSTR = 0

#Cycle through all STRs in the database
for STR in database[0]:
    #skip first entry in database as this contains the headings
    if STR == "name":
        continue

    #lastMatch tracks the position of the last matched STR
    #Reset lastMatch
    lastMatch = 0
    #j is used as an internal counter for back to back match count
    j = 0

    #Increament posSTR count
    posSTR += 1

    #Cycle through DNA sequence to check for the current STR
    for i in range(0, (len(sequence) - len(STR) + 1)):

        #If the current sub-string of the DNA sequence matched the STR then a match has been found
        if STR == sequence[i:i+len(STR)]:

            #print(STR)
            #print(i)

            #If counter is 0 increment to 1 (This is needed to prevent a comparision with lastMatch occuring on the first match that is found)
            if j == 0:
                j = 1

            #If this match is directly after the previous match then increment the counter
            elif lastMatch == (i - len(STR)):
                j += 1

            else:
                j = 1

            #print(j)

            #Set lastMatch equal to i
            lastMatch = i

            #Change count value if the j count is higher than the stored count value
            if j > count[posSTR]:
                count[posSTR] = j
#print(count)


#---------------------------------------------------------------------
#Compare STR counts to each persons STR counts to try and find a match

#Cycle through database to check if all counts match the STR counts calculate above
for person in database:
    #skip first entry in database as this contains the headings
    if person[0] == "name":
        continue

    #MatchedSTR tracks the number of STR countsthat have been matched for the current person
    #Reset matchedSTR
    matchedSTR = 0
    #i counts the position within the count list
    i = 1

    for cntSTR in person:

        #skip first entry in database as this contains the perosns name
        if cntSTR.isalpha():
            #print(cntSTR)
            continue

        #If cnt is equal to STR count then continue
        if int(cntSTR) == count[i]:

            matchedSTR += 1

        #If there is not a match end the check on this person
        else:
            break

        #Check if mtachedSTR count is equal to the total number of STRs
        if matchedSTR == (len(database[0]) - 1):

            #Print matched name
            print(person[0])
            exit()

        #Increment i
        i += 1

#Reached the end of the check and no complete macthed found so print No Match
print("No Match")
exit()