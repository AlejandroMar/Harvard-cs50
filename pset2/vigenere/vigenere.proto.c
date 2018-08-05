#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, string argv[])
{

    if (argc == 2)
    {
        int argvLength = strlen(argv[1]);
        //Check if all charaters in argv are alphabetic
        for (int i = 0; i < argvLength; i++)
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
        int keywordIndex = 0;
        for (int i = 0; i < plainTextLength; i++)
        {

            if (isupper(plainText[i]))
            {
                if (isupper(keyword[keywordIndex]))
                {
                int encritedASCII = (plainText[i] - 65 + keyword[keywordIndex] - 65) % 26 + 65;
                ciphertext[i] = encritedASCII;
                keywordIndex++;
                keywordIndex = keywordIndex % keywordLength;
                continue;
                }

                if (islower(keyword[keywordIndex]))
                {
                int encritedASCII = (plainText[i] - 65 + keyword[keywordIndex] - 97) % 26 + 65;
                ciphertext[i] = encritedASCII;

                keywordIndex++;
                keywordIndex = keywordIndex % keywordLength;
                continue;
                }
            }
            else if (islower(plainText[i]))
            {
                if (isupper(keyword[keywordIndex]))
                {
                int encritedASCII = (plainText[i] - 97 + keyword[keywordIndex] - 65) % 26 + 97;
                ciphertext[i] = encritedASCII;

                keywordIndex++;
                keywordIndex = keywordIndex % keywordLength;
                continue;
                }

                if (islower(keyword[keywordIndex]))
                {
                int encritedASCII = (plainText[i] - 97 + keyword[keywordIndex] - 97) % 26 + 97;
                ciphertext[i] = encritedASCII;

                keywordIndex++;
                keywordIndex = keywordIndex % keywordLength;
                continue;
                }
            }
            else
            {
                ciphertext[i] = plainText[i];
            }
        }

        printf("ciphertext: %s\n", ciphertext);
        return 0;
    }
    else
    {
        printf("Please type two arguments\n");
        return 1;
    }
}