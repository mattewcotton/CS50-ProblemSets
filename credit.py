#Import get string from cs50
from cs50 import get_string

#Get user to enter credit card number
cardNo = get_string("Enter card number without spaces or hyphens: ")

#Convert string to integr digits
digits = [int(d) for d in cardNo]

#Check card type
if len(cardNo) == 15 and digits[0] == 3 and (digits[1] == 4 or digits[1] == 7):
    cardType = "AMEX"
elif len(cardNo) == 16 and digits[0] == 5 and (digits[1] == 1 or digits[1] == 2 or digits[1] == 3 or digits[1] == 4 or digits[1] == 5):
    cardType = "MASTERCARD"
elif (len(cardNo) == 13 or len(cardNo) == 16) and digits[0] == 4:
    cardType = "VISA"
else:
    cardType = "INVALID"

#If cardType is INVALID then print Invalid and end program here
if cardType == "INVALID":
    print(cardType)
    exit()

#Calculate and check checksum
multi = []
for i in range(0, len(digits) - 1, 2):
    multi.append(digits[len(digits) - 2 - i] * 2)
total = 0
for i in range(len(multi)):
    if multi[i] > 9:
        total += 1 + (multi[i] - 10)
    else:
        total += multi[i]
for i in range(0, len(digits), 2):
    total += digits[len(digits) - 1 - i]

if total % 10 != 0:
    cardType = "INVALID"

#Print output (card type or invalid)
print(cardType)
exit()