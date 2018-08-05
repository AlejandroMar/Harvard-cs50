#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

//refactored code
//next fase get rid of magic numbers

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
        string keyword = argv[1];
        int keywordLength = strlen(keyword);
        string plainText = get_string("plaintext: ");
        int plainTextLength = strlen(plainText);
        char ciphertext[plainTextLength + 1];
        //found this bug and searched for it in stackoverflow
        ciphertext[plainTextLength] = '\0';
        int keywordIndex = 0, encritedASCIIUpper, encritedASCIIlower;

        for (int i = 0; i < plainTextLength; i++)
        {

            if (isupper(plainText[i]))
            {
                if (isupper(keyword[keywordIndex % keywordLength]))
                {
                    encritedASCIIUpper = (plainText[i] - 65 + keyword[keywordIndex % keywordLength] - 65) % 26 + 65;
                }

                else if (islower(keyword[keywordIndex % keywordLength]))
                {
                    encritedASCIIUpper = (plainText[i] - 65 + keyword[keywordIndex % keywordLength] - 97) % 26 + 65;
                }

                ciphertext[i] = encritedASCIIUpper;
                keywordIndex++;
            }
            else if (islower(plainText[i]))
            {
                if (isupper(keyword[keywordIndex % keywordLength]))
                {
                    encritedASCIIlower = (plainText[i] - 97 + keyword[keywordIndex % keywordLength] - 65) % 26 + 97;


                }
                else if (islower(keyword[keywordIndex % keywordLength]))
                {
                    encritedASCIIlower = (plainText[i] - 97 + keyword[keywordIndex % keywordLength] - 97) % 26 + 97;
                }

                ciphertext[i] = encritedASCIIlower;
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