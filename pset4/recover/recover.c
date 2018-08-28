#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdint.h>
typedef uint8_t  BYTE;

int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        fprintf(stderr, "please give only one argument\n");
        return 1;
    }

    char *infile = argv[1];
    FILE *inptr = fopen(infile, "rb");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
    }

    BYTE *buffer = malloc(512 * sizeof(BYTE));
    if (buffer == NULL)
    {
        return 2;
    }

    //this variable helps to define if there we already found a jpeg
    bool found = false;
    // helps to give the number for each photo
    int count = 0;
    //in this variable store the return number of elemtes read by fread()
    int numberRead = 0;

    //feof() end of file
    while (!feof(inptr))
    {
        //checks until we find the first photo
        if (!found)
        {
            numberRead = fread(buffer, sizeof(BYTE), 512, inptr);
            if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
            {
                found = true;
            }
        }

        if (found)
        {
            //after finding the first photo we stay in this condtion
            char *filename = malloc(1 * sizeof(char));
            if (filename == NULL)
            {
                return 2;
            }
            sprintf(filename, "%03i.jpg", count);
            FILE *img = fopen(filename, "w");
            if (img == NULL)
            {
                return 2;
            }

            //begin writing
            fwrite(buffer, sizeof(BYTE), numberRead, img);
            numberRead = fread(buffer, sizeof(BYTE), 512, inptr);
            //check if it's not a new photo
            while (!(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0))
            {
                fwrite(buffer, sizeof(BYTE), numberRead, img);
                numberRead = fread(buffer, sizeof(BYTE), 512, inptr);
                //this would mean we are at the end of the file so write and break
                if (numberRead < 512)
                {
                    //this is why we used the numberRead variable to just wirte the elements that where read
                    fwrite(buffer, sizeof(BYTE), numberRead, img);
                    break;
                }
            }
            fclose(img);
            //free the dinamically allocated memory to avoid memory leaks
            free(filename);
            count++;
        }
    }
    //free the dinamically allocated memory to avoid memory leaks
    free(buffer);
    return 0;
}



