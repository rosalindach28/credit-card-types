# credit-card-types
C program that determines whether a number is a valid American Express, MasterCard (with some exceptions), or Visa credit card number.  Following prompt from CS50 course.
User is asked to input a number (sequence of numbers) representative of a credit card number (no hyphens).
Program then checks input to determine the validity of the card number through the implementation of Luhn's algorithm
as well as the credit card company it could be associated with (American Express, MasterCard, or Visa)
based on the following criteria:
- American Express uses 15-digit numbers, MasterCard uses 16-digit numbers, and Visa uses 13 and 16-digit numbers.
- All American Express numbers start with 34 or 37.
- All Visa numbers start with 4.
- Most MasterCard numbers start with 51, 52, 53, 54, or 55 (there are exceptions).
Once the program is done executing, the user will see one of four options printed in the terminal/console:
AMEX, MASTERCARD, VISA, or INVALID.

To run program (VS Code, Windows)
simply press Run button near top right corner.
Must have CodeRunner extension installed.
