#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("error\n");
        return 1;
    }
    
    // open memory card
    char *infile = argv[1];
    FILE *inptr = fopen(infile, "r");
    if (!inptr)
    {
        printf("error\n");
        return 1;
    }
    
    // declare buffer and stuff
    BYTE buffer[512];
    int jpeg_count = 0;
    FILE *outptr = NULL;
    char filename[8];
    
    // LOOP: this UNTIL eof
    while (fread(buffer, 512, 1, inptr) == 1)
    {
        // IF jpeg
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // IF not first jpeg file
            if (jpeg_count > 0)
            {
                // close previous jpeg file
                fclose(outptr);
            }
            
            // create a new jpeg
            sprintf(filename, "%03i.jpg", jpeg_count);
            
            // open new image file
            outptr = fopen(filename, "w");
            
            // add 1 to jpeg counter
            jpeg_count++;
        }
        // write buffer into new jpeg if jpeg found before
        if (jpeg_count > 0)
        {
            fwrite(buffer, 512, 1, outptr);
        }
    }
        
    // close files
    fclose(outptr);
    fclose(inptr);
    // return
    return 0;
}
