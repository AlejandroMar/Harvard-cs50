#include <stdio.h>
#include <cs50.h>
#include <string.h>
//for atoi
#include <stdlib.h>
#include <ctype.h>

#define UPPCASE 65
#define LOWCASE 97
#define ALPHALENGTH 26

//refactored code


int main(int argc, string argv[])
{

    if (argc != 2)
    {
        printf("Please type two arguments\n");
        return 1;
    }
    else
    {
        //Check if all charaters in argv are alphabetic
        for (int i = 0, n = strlen(argv[1]); i < n; i++)
        {
            //check for each letter
            if (!isalpha(argv[1][i]))
            {
                printf("The key must contain only alphabetic letters\n");
                return 1;
            }
        }

        //declare variables
        string keyword = argv[1];
        int keywordLength = strlen(keyword);
        string plainText = get_string("plaintext: ");
        int plainTextLength = strlen(plainText);
        // this array is going to give me garbage values unless explicitly set a null operator
        char ciphertext[plainTextLength + 1];
        ciphertext[plainTextLength] = '\0';
        int keywordIndex = 0, encriptedASCIIUpper, encriptedASCIIlower;

        //the text gets encripted here inside the loop
        for (int i = 0; i < plainTextLength; i++)
        {
            //check plainText case
            if (isupper(plainText[i]))
            {
                //check key[i] case
                // keywordIndex % keywordLength, allows me to wrap around the key, so I never get an index > keyLength
                if (isupper(keyword[keywordIndex % keywordLength]))
                {
                    //inside parenthesis I turn the code to alphabetical index, then wrap around alphabet and then go back to ASCII code
                    encriptedASCIIUpper = (plainText[i] - UPPCASE + keyword[keywordIndex % keywordLength] - UPPCASE) % ALPHALENGTH +  UPPCASE;
                }

                else if (islower(keyword[keywordIndex % keywordLength]))
                {
                    encriptedASCIIUpper = (plainText[i] - UPPCASE + keyword[keywordIndex % keywordLength] - LOWCASE) % ALPHALENGTH + UPPCASE;
                }

                ciphertext[i] = encriptedASCIIUpper;
                keywordIndex++;
            }
            else if (islower(plainText[i]))
            {
                if (isupper(keyword[keywordIndex % keywordLength]))
                {
                    encriptedASCIIlower = (plainText[i] - LOWCASE + keyword[keywordIndex % keywordLength] - UPPCASE) % ALPHALENGTH + LOWCASE;
                }
                else if (islower(keyword[keywordIndex % keywordLength]))
                {
                    encriptedASCIIlower = (plainText[i] - LOWCASE + keyword[keywordIndex % keywordLength] - LOWCASE) % ALPHALENGTH + LOWCASE;
                }

                ciphertext[i] = encriptedASCIIlower;
                keywordIndex++;
            }
            else
            {
                ciphertext[i] = plainText[i];
            }
        }

        printf("ciphertext: %s\n", ciphertext);
        return 0;
    }
}