#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    //Check that there are exactly 2 command line argument
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }
    //Try to open file name given by command line argument 2
    FILE *input = fopen(argv[1], "r");
    //Check if file could be read/opened
    if (input == NULL)
    {
        printf("Could not open file %s.\n", argv[1]);
        return 1;
    }
    //Declare a 512 Byte block/buffer, filename, counter and jpeg pointer
    BYTE buffer[512];
    int fileCount = 0;
    char filename[9];
    FILE *jpeg = NULL;

    //Loop through every 512 B blocks in file input
    while (true)
    {
        //Load i'th 512 B block of data
        size_t size = fread(buffer, sizeof(BYTE), 512, input);

        //Check if end of file has been reached
        if (size == 0 && feof(input))
        {
            break;
        }

        //Check if jpeg header values are in current 512 Byte block
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            //If this is not the first jpeg to be found then close the last one
            if (jpeg != NULL)
            {
                fclose(jpeg);
            }
            //Create new file name in the format XXX.jpg
            sprintf(filename, "%03i.jpg", fileCount);
            //Open new jpeg file
            jpeg = fopen(filename, "w");
            //write 512 Byte block to jpeg
            fwrite(buffer, sizeof(BYTE), size, jpeg);
            //Increase file count by 1
            fileCount++;
        }
        //If this block doesn't start with the jpeg header values and file count is non-zero then add this block to the currently open jpeg
        else if (fileCount > 0)
        {
            fwrite(buffer, sizeof(BYTE), size, jpeg);
        }
    }
    //Close last jpeg file
    fclose(jpeg);
    //Close the input file
    fclose(input);
}