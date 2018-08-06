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
    int count = 0;
    while (cardNumberToCount != 0)
    {
        cardNumberToCount /= 10;
        count++;
    }

     //check if it's valid
    long long numberToValidate = cardNumber;
    long long sum = 0;
    bool isValid = false;
    for (int i = 0; i <= count; i++)
    {
        long long temp1 = numberToValidate % (long long) pow(10, (i + 1)) / (long long) pow(10, i);
        //printf("temp1 %lld\n", temp1);
        if (i % 2 != 0 )
        {
            temp1 *= 2;
            if (temp1 > 9)
            {
                temp1 = temp1 % 10 + temp1 / 10;
                //printf("%lld + %lld\n", temp1 % 10, temp1 / 10);
            }
            sum += temp1;
            //printf("temp1 * 2 = %lld\n", temp1);
            //printf("Sum %lld\n", sum);
        }
        else
        {
            sum += temp1;
            //printf("temp1 = %lld\n", temp1);
            //printf("Sum %lld\n", sum);
        }
    }

    if (sum % 10 == 0)
    {
        isValid = true;
        //printf("credit card is valid\n");
    }

    if (isValid)
    {
        if (count == 15)
        {
            long long startNum = numberToValidate % (long long) pow(10, 15) / (long long) pow(10, 13);
            if (startNum == 34 || startNum == 37)
            {
                printf("AMEX\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else if (count == 13 || count == 16)
        {

            if (count == 16)
            {
             long long startNum = numberToValidate % (long long) pow(10, 16) / (long long) pow(10, 15);
                 if (startNum == 4)
                 {
                    printf("VISA\n");
                 }
                 else if(startNum == 5)
                 {
                    startNum = numberToValidate % (long long) pow(10, 16) / (long long) pow(10, 14);
                    //printf("with 5: %lld\n", startNum);
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
            else if (count == 13)
            {
                long long startNum = numberToValidate % (long long) pow(10, 13) / (long long) pow(10, 12);
                if (startNum == 4)
                {
                    printf("VISA\n");
                }
                else
                {
                    printf("INVALID\n");
                }
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






    //long long firstNumber = cardNumber % (long long) pow(10, 15) / (long long) pow(10, 14);



    //%lld to print a long long
    //printf("Number length: %d\n", count);
   // printf("Number %lld\n", cardNumber);
   // printf("Sum %lld\n", sum);
   // printf("Number %lld\n", firstNumber);
    return 0;
}