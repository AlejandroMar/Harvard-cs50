#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define UPPERCASEINDEX 65
#define LOWERCASEINDEX 97
#define ALPHABETLENGTH 26

int main(int argc, string argv[])
{
    if (argc == 2)
    {
        //turn the string into a int
        int k =  atoi(argv[1]);
        string p = get_string("plaintext: ");
        int pLength = strlen(p);
        //because C needs a fixed length for arrays I use the length of the string as the length of the array
        char ciphertext[pLength];

        for (int i = 0; i < pLength; i++)
        {
            // Checks if the given character is a lowercase alphabetic letter
            if (isupper(p[i]))
            {
                //Pi = p[i] UPPERCASEINDEX = A in ASCII code k=key
                //creates an alphabetical index by substracting the ASCII code, does the algorithm and resets the ASCII code
                int encritedASCII = (p[i] - UPPERCASEINDEX + k) % ALPHABETLENGTH + UPPERCASEINDEX;
                //string arr
                ciphertext[i] = encritedASCII;

            }
            else if (islower(p[i]))
            {
                int encritedASCII = (p[i] - LOWERCASEINDEX + k) % ALPHABETLENGTH + LOWERCASEINDEX;
                //string arr
                ciphertext[i] = encritedASCII;
            }
            else
            {
                //if it is not an alpha character
                ciphertext[i] = p[i];
            }
        }
        printf("ciphertext: %s\n", ciphertext);
        return 0;
    }
    else
    {
        printf("Please type only two arguments");
        return 1;
    }
}