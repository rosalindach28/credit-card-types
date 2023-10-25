// Determine credit card type based on given number (no hyphens)

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

bool isNumeric(const char *userInput);
long long get_card(void);
int get_length(long long cardNum);
int LuhnsAlgo(long long num, int length);
long long starting_digits(long long num);
void card_type(int length, long long num, long long firstTwoDigits, int lastDigitOfSums);

int main(void)
{
   // long long number = 4003600000000014; // for testing purposes
    long long number = get_card();
    int length1 = get_length(number);
    int sumsLastDigit = LuhnsAlgo(number, length1);
    long long firstTwo = starting_digits(number);
    card_type(length1, number, firstTwo, sumsLastDigit);
}

// checks if user input contains only numerical characters
bool isNumeric(const char *userInput)
{
    while (*userInput)
    {
        if (*userInput < '0' || *userInput > '9')
        {
            return false;
        }
        userInput++;
    }
    return true;
}


// prompt user for credit card number
long long get_card(void)
{
    long long cardNumber;
    char input[20];

// input validation
// makes sure user inputs valid numerical values
// no letters, hyphens
    do
    {
    printf("Enter card number: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;  // remove the trailing newline character from input
    } while (!isNumeric(input));

    // Convert the valid number as string to a long
        cardNumber = strtoll(input, NULL, 10); // base 10 conversion

        // Check if the conversion was successful
        if (cardNumber == 0 && input[0] != '0')
        {
            printf("Conversion error or invalid input!\n");
            return 1;
        }
        else
        {
            //printf("Stored as a long: %lld\n", cardNumber);
            return cardNumber;
        }
}

// provides the length of the card number as a numerical value
// important for determining the type and validity of card
int get_length(long long cardNum)
{
    // convert number to string using sprintf to figure out length
    // put the converted number into a string (sprintf function)
    char cardString[20]; // string where user input will be stored
    sprintf(cardString, "%lld", cardNum);
    int length = strlen(cardString);
    return length;
}

// implements Luhn's algorithm based on given card number
// returns last digit of sums
// indicating valid or invalid card number
int LuhnsAlgo(long long num, int cardLength)
{
    int numbers[cardLength];
    int other[cardLength / 2];  // digits not multiplied by 2
    int times2[cardLength / 2]; // every other digit multiplied by 2
    int index = 0;
    int j = 0; // j,k, and m are array indices
    int k = 0;
    int m = 0;
    int sum1 = 0;           // sum of the digits multiplied by 2
    int sum2 = 0;           // sum of the other digits NOT multiplied
    int totalSum = 0;      // sum1+sum2
    int lastDigitOfSums; // of total sum
    long long num2;         // sequence of the digits multiplied by 2
    long long num3;         // sequence of digits NOT multiplied by 2

    // extract individual digits from original card number
    // store digits in an array to manipulate later
    // when extracted, digits are stored in array in reverse order

    while (num > 0)
    {
        int mod = num % 10; // split last digit from number
        // printf("%d\n",mod); //print the digit.
        numbers[index] = mod;
        num = num / 10;
        index++;
    }
    /*
    1. Multiply every other digit by 2, starting with the number’s second-to-last digit.
    starting from the end of number so the second-to-last digit is at index 1
    store results in new array
    */
    for (int i = 1; i < cardLength; i += 2)
    {
        // printf("%d ", numbers[i]);
        for (int j = 0; j < i; j++)
        {
            times2[j] = numbers[i] * 2; // stores resulting products in times2 array
        }
        //  printf("%d", times2[j]);

        // 2. add together each products' digits individually
        // extract individual digits then add them together

        num2 = times2[j]; // put array elements in a long
        while (num2 > 0)
        {
            int digit = num2 % 10;
            sum1 += digit;
            num2 = num2 / 10;
        }
    }
    // printf("Sum of products' digits is: %d\n", sum1);

    /*
    3.Now add together all the other digits that weren’t multiplied by 2 (starting from the end).
    Save these in a new array to have them stored for upcoming changes
    then save array values as a long for easier extraction of digits
    */

    for (int k = 0; k < cardLength; k += 2)
    {
        // printf("%d ", numbers[k]);
        for (int m = 0; m < cardLength / 2; m++)
        {
            other[m] = numbers[k];
        }
        // printf("%d", other[m]);

        num3 = other[m];
        // printf("%lld ", num3);
        while (num3 > 0)
        {
            int modulo = num3 % 10;
            sum2 += modulo;
            num3 = num3 / 10;
        }
    }
    // printf("Sum of digits not multiplied by 2 is: %d\n", sum2);

    /*
    4. Add the first sum (digits * 2) to the sum of the digits that weren’t multiplied by 2 (sum2)
    Check the last digit of this total sum
    If the total’s last digit is 0, the card number is valid
    If last digit is not equal to zero, card number is invalid
    */  
    totalSum = sum1 + sum2;
    lastDigitOfSums = totalSum % 10;
    return lastDigitOfSums;
} // end of function

// function to get the first 2 numbers of the card number
// divide card number by 10 until only 2 digits left
// will help determine the type of card it is
long long starting_digits(long long num)
{
    long long first2 = num;

    while (first2 >= 100) // anything below 100 is 2 numbers or less
    {
        first2 /= 10;
    }
    return first2;
}

/*
determines validity of card by checking length, starting digit(s) of card number,
and last digit of total sum
American Express uses 15-digit numbers
MasterCard uses 16-digit numbers, and Visa uses 13-16-digit numbers
if valid, card company will be printed
*/
void card_type(int length, long long num, long long firstTwoDigits, int lastDigitOfSums)
{
    // grab only first digit of card number to check VISA cards
    // other cards use the first 2 starting digits to check
    long long firstDigit = num;
    while (firstDigit >= 10)
    {
        firstDigit /= 10;
    }
    // printf("First: %lld\n", firstDigit); // checking output

    // Value of last digit of total sum is stored in lastDigitOfSums

    if ((length >= 13 && length <= 16) && firstDigit == 4 && lastDigitOfSums == 0)
    {
        printf("VISA\n");
    }
    else if (length == 16 && (firstTwoDigits == 51 || firstTwoDigits == 52 || firstTwoDigits == 53 || firstTwoDigits == 54 || firstTwoDigits == 55) && lastDigitOfSums == 0)
    {
        printf("MASTERCARD\n");
    }
    else if (length == 15 && (firstTwoDigits == 34 || firstTwoDigits == 37) && lastDigitOfSums == 0)
    {
        printf("AMEX\n");
    }
    else
    {
        printf("INVALID\n");
    }
} // end of program