from cs50 import get_string


#Get txt passage input from user
text = get_string("Text: ")

#Caclualte the number of letters, words and sentences
words = len(text.split())
sentences = sum((c == "." or c == "?" or c == "!") for c in text)
letters = sum(c.isalpha() for c in text)

#Calculate the Coleman-Liau index
index = 0.0588 * ((letters / words) * 100) - 0.296 * ((sentences / words) * 100) - 15.8

#Print result
if index < 1:
    print("Before Grade 1")
elif index >= 16:
    print("Grade 16+")
else:
    print(f"Grade {index:0.0f}")