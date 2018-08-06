#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    long long cardNumber;
    do
    {
        cardNumber = get_long_long("Credit Card number: ");
    }
    while (cardNumber <= 0);

    long long cardNumberToCount = cardNumber;
    //check length of number
    int numberOfDigits = 0;
    while (cardNumberToCount != 0)
    {
        cardNumberToCount /= 10;
        numberOfDigits++;
    }

    //check if it's valid
    long long sum = 0;
    bool isValid = false;
    for (int i = 0; i <= numberOfDigits; i++)
    {
        long long temp1 = cardNumber % (long long) pow(10, (i + 1)) / (long long) pow(10, i);
        if (i % 2 != 0 )
        {
            temp1 *= 2;
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
        if (numberOfDigits == 13)
            {
                long long startNum = cardNumber  / (long long) pow(10, 12);
                if (startNum == 4)
                {
                    printf("VISA\n");
                }
                else
                {
                    printf("INVALID\n");
                }
            }

        if (numberOfDigits == 15)
        {
            long long startNum = cardNumber / (long long) pow(10, 13);
            if (startNum == 34 || startNum == 37)
            {
                printf("AMEX\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        if (numberOfDigits == 16)
        {
             long long startNum = cardNumber / (long long) pow(10, 15);
                 if (startNum == 4)
                 {
                    printf("VISA\n");
                 }
                 else if(startNum == 5)
                 {
                    startNum = cardNumber / (long long) pow(10, 14);
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
        else
        {
            printf("INVALID\n");
        }
    }

    return 0;
}