#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // declare n first
    int height;
    do
    {
        height = get_int("Positive integer: ");
    }
    while (height < 0 || height > 23);

    //this loop prints the rows
    for (int i = 1; i <= height; i++)
    {
        // this inner loops print the columns
        // nth-space = height - row-number
        for (int j = 0; j < (height - i); j++)
        {
            printf(" ");
        }
        // nth-hash = row-number
        for (int k = 0; k < i; k++)
        {
            printf("#");
        }
        // space between
        printf("  ");

        // just inverse the columns
        for (int k = 0; k < i; k++)
        {
            printf("#");
        }

        printf("\n");

    }
}