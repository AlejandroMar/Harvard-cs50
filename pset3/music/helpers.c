// Helper functions for music
#include <stdio.h>
#include <cs50.h>

#include "helpers.h"
//my imports
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    // TODO
    int numerator = fraction[0] - '0';
    int denominator = fraction[2] - '0';
    int eights = 8 / denominator * numerator;

    return eights;
}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{

    char currentNote = note[0];
    char accidental;
    //interval is the numerator in the formula for note frequencies
    int interval = 0;
    int octave;
    int defaultOctave = 4;

    //Basic notes interval numbers
    int B = 2;
    int C = 3;
    int D = 5;
    int E = 7;
    int F = 8;
    int G = 10;

    //base frequency
    int A = 440;
    //Set the octave and the accidental varibles
    //In case of accidental change the interval accordingly
    if (strlen(note) == 3)
    {
        accidental = note[1];
        octave = note[2] - '0';

        if (accidental == '#')
        {
            interval += 1;
        }
        else if (accidental == 'b')
        {
            interval -= 1;
        }
    }
    //set octave varible in case of length 2
    if (strlen(note) == 2)
    {
        octave = note[1] - '0';
    }



    //set intervals depending on notes
    if (currentNote == 'B')
    {
        interval += B;
    }
    else if (currentNote == 'C')
    {
        interval += C;
    }
    else if (currentNote == 'D')
    {
        interval += D;
    }
    else if (currentNote == 'E')
    {
        interval += E;
    }
    else if (currentNote == 'F')
    {
        interval += F;
    }
    else if (currentNote == 'G')
    {
        interval += G;
    }

    //use formula for exponents
    float exponent = (float) interval / (float) 12;

    //calculate frequencies depending on the case
    if ((currentNote == 'A' || currentNote == 'B') && octave >= 4)
    {
        octave = pow(2, (abs(octave - defaultOctave)));
        float freq = round(A * pow(2, (exponent)) * octave);
        return freq;
    }
    else if ((currentNote == 'A' || currentNote == 'B') && octave < 4)
    {
        octave = pow(2, (abs(octave - defaultOctave)));
        float freq = round(A * pow(2, (exponent)) / octave);
        return freq;
    }
    else if (octave > 4)
    {
        octave = pow(2, (abs(octave - defaultOctave - 1)));
        float freq = round(A * pow(2, (exponent)) * octave);
        return freq;
    }
    else if (octave <= 4)
    {
        octave = pow(2, (abs(octave - defaultOctave - 1)));
        float freq = round(A * pow(2, (exponent)) / octave);
        return freq;
    }

    return 0;


}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    // TODO
    if (strlen(s) == 0)
    {
        return true;
    }
    else
    {
        return false;
    }

    return 0;
}
