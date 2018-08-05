#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // declare n first
    int height;
    do
    {
        height = get_int("size: ");
    }
    while (height < 0 || height > 23);

    //this loop prints the rows
    for (int i = 1; i <= height; i++)
    {
        //this inner loops print the columns
        // nth-space = height - row-number
        for (int j = 0; j < (height - i); j++)
        {
            printf(" ");
        }
        // nth-hash = row-number + 1
        for (int k = 0; k < (i + 1); k++)
        {
            printf("#");
        }
        //break line
        printf("\n");
    }
}