#import get_int from cs50
from cs50 import get_int

#Get height input (h) from user within loop to check that it is between 1 and 8
while True:
    h = get_int("Height: ")
    if h > 0 and h < 9:
        break

#Print the two pyramids to height h
for i in range(h):
    print(" " * (h - i - 1), end="")
    print("#" * (1 + i), end="  ")
    print("#" * (1 + i))
