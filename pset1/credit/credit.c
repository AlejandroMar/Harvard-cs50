#include <stdio.h>
#include <cs50.h>
#include <math.h>
//define the base for the pow function
#define BASE 10

//for more info and instructions: https://docs.cs50.net/2018/x/psets/1/credit/credit.html

int main(void)
{
    long long cardNumber;
    //prompt user for Number make shure is positve
    do
    {
        cardNumber = get_long_long("Credit Card number: ");
    }
    while (cardNumber <= 0);

    //Need to copy number because it will be divided until cero
    long long cardNumberToCount = cardNumber;

    //check for number's length
    int numberOfDigits = 0;
    while (cardNumberToCount != 0)
    {
        cardNumberToCount /= 10;
        numberOfDigits++;
    }

    //check if it's valid
    long long sum = 0;
    bool isValid = false;
    // this loop checks if the number is a valid one uses Luhn’s algorithm.
    // * Multiply every other digit by 2, starting with the number’s second-to-last digit, and then add those products' digits together.
    // * Add the sum to the sum of the digits that weren’t multiplied by 2.
    // * If the total’s last digit is 0 (or, put more formally, if the total modulo 10 is congruent to 0), the number is valid!
    for (int i = 0; i <= numberOfDigits; i++)
    {
        // it isolates the number
        long long temp1 = cardNumber % (long long) pow(BASE, (i + 1)) / (long long) pow(BASE, i);
        if (i % 2 != 0)
        {
            temp1 *= 2;
            //I need to split the number if it has more than one digit
            //add those products' digits (i.e., not the products themselves) together: exm 14, 1 + 4
            if (temp1 > 9)
            {
                temp1 = temp1 % 10 + temp1 / 10;
            }
            sum += temp1;
        }
        else
        {
            sum += temp1;
        }
    }
    //if the total modulo 10 is congruent to 0, the number is valid!
    if (sum % 10 == 0)
    {
        isValid = true;
    }

    if (!isValid)
    {
        printf("INVALID\n");
    }
    else
    {
        //every card has a set length and a prefix number
        //check for Visa
        if (numberOfDigits == 13)
        {
            long long startNum = cardNumber  / (long long) pow(BASE, 12);
            if (startNum == 4)
            {
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        //check for AMEX
        if (numberOfDigits == 15)
        {
            long long startNum = cardNumber / (long long) pow(BASE, 13);
            if (startNum == 34 || startNum == 37)
            {
                printf("AMEX\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        //check for VISA OR MASTERCARD
        if (numberOfDigits == 16)
        {
            long long startNum = cardNumber / (long long) pow(BASE, 15);
            if (startNum == 4)
            {
                printf("VISA\n");
            }
            else if (startNum == 5)
            {
                startNum = cardNumber / (long long) pow(BASE, 14);
                if (startNum == 55 || startNum == 54 || startNum == 53 || startNum == 52 || startNum == 51)
                {
                    printf("MASTERCARD\n");
                }
                else
                {
                    printf("INVALID\n");
                }
            }
            else
            {
                printf("INVALID\n");
            }
        }
        //if the number is valid but the length is other than 15 13 or 16
        else
        {
            printf("INVALID\n");
        }
    }

    return 0;
}