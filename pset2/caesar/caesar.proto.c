#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    if(argc == 2)
    {
        int k =  atoi(argv[1]);
        string p = get_string("plaintext: ");
        int pLength = strlen(p);
        char ciphertext[pLength];

        for (int i = 0; i < pLength; i++)
        {
            if(isalpha(p[i]) && isupper(p[i]))
            {
                //this is Pi
                int indexVal = p[i] - 65;
                //this is Ci
                int encriptedAlphaIndex = (indexVal + k) % 26;
                int encritedASCII =  encriptedAlphaIndex + 65;

                int sisas = (p[i] - 65 + k) % 26 + 65;
                //string arr
                ciphertext[i] = sisas;
                //printf("letter: %c ASCIIcode: %i alphaIndex: %i encriptedCindex is: %i encritedASCII: %c\n", p[i], (int) p[i], IndexVal, encriptedAlphaIndex, encritedASCII);
            }else if(isalpha(p[i]) && islower(p[i]))
            {
                int indexVal = p[i] - 97;
                //this is Ci
                int encriptedAlphaIndex = (indexVal + k) % 26;
                int encritedASCII =  encriptedAlphaIndex + 97;
                //string arr
                ciphertext[i] = encritedASCII;
            }
            else
            {
                ciphertext[i] = p[i];

            }
        }
        printf("ciphertext: %s\n", ciphertext);

       // printf("the key is: %i\n", k);
        return 0;

       // printf("arg 2 is %i p is %s length of p is %i", k, p, pLength);
    }
    else
    {
        printf("Please type only two arguments");
        return 1;
    }
}