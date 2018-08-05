#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    //declare variable
    float change;
    //prompt for user input
    do
    {
        change = get_float("Change owed: ");
    }
    //avoid negative numbers
    while (change < 0);

    // round the decimals and turn it into an integer
    int changeAsInt = roundf(change * 100);;

    // define coins
    int quarter = 25;
    int dime = 10;
    int nickel = 5;
    int pennie = 1;

    // count will hold the number of coins given back to user
    int counter = 0;

    //substract from change from grThan to smThan update counter
    if (quarter <= changeAsInt)
    {
        counter += changeAsInt / quarter;
        changeAsInt = changeAsInt % quarter;
    }

    if (dime <= changeAsInt)
    {
        counter += changeAsInt / dime;
        changeAsInt = changeAsInt % dime;
    }

    if (nickel <= changeAsInt)
    {
        counter += changeAsInt / nickel;
        changeAsInt = changeAsInt % nickel;
    }

    if (pennie <= changeAsInt)
    {
        counter += changeAsInt / pennie;
        changeAsInt = changeAsInt % pennie;
    }
    //print result with a line break
    printf("%i\n", counter);

}


