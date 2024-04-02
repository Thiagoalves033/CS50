import sys
import random
from pyfiglet import Figlet

figlet = Figlet()
fontlist = figlet.getFonts()
f = random.choice(fontlist)

# Proper usage
if len(sys.argv) not in [1, 3]:
    print("Incorrect usage.")
    sys.exit(1)
elif len(sys.argv) == 3 and sys.argv[2] not in fontlist:
    print("Incorrect font name or not present in list.")
    sys.exit(1)
elif len(sys.argv) == 3 and sys.argv[1] not in ["-f", "--font"]:
    print("First command-line argument is incorrect.")
    sys.exit(1)

# Printing the text
text = input("Input: ")
print("Output: ")

if len(sys.argv) == 1:
    figlet.setFont(font=f)
    print(figlet.renderText(text))

elif len(sys.argv) == 3:
    figlet.setFont(font=sys.argv[2])
    print(figlet.renderText(text))
