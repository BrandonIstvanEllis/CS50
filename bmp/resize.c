#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./copy n infile outfile\n");
        return 1;
    }

    // get factor to resize image
    int n = atoi(argv[1]);
    
    //make sure n is between 1 and 100
    if (n < 1 || n > 100)
    {
        printf("Error, n must be between 1 and 100 inclusive");
        return 5;
    }
    
    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    
    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    //make copies of the file header and infoheader to adjust their values for the outfile, while still being able to
    //reference the original values for padding etc
    
    BITMAPFILEHEADER bfout = bf;
    BITMAPINFOHEADER biout = bi;
    
    //make appropriate adjustments to the file header and info header copies to resize them by a factor of n
    biout.biWidth = bi.biWidth * n;
    biout.biHeight = bi.biHeight * n;
    
    // determine padding for reading and padding for the outfile
    int paddingread =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int paddingout = (4 - (biout.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    //calculate the file size
    //add the size of the file header and info header, as well as the size of all the pixels
    //height must use abs since height may be negative to draw top to bottom
    bfout.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + sizeof(RGBTRIPLE) * biout.biWidth * abs(biout.biHeight) + abs(biout.biHeight) * paddingout;

    // write outfile's BITMAPFILEHEADER
    fwrite(&bfout, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&biout, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        //iterate over each line n times
        for (int x = 0; x < n; x++)
        {
            // iterate over pixels in scanline
            for (int j = 0; j < bi.biWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
               fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
               
               // write RGB triple to outfile n times
                for (int y = 0; y < n; y++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }

            //add padding
            for (int k = 0; k < paddingout; k++)
            {
                fputc(0x00, outptr);
            }
            
            //use fseek to go back to the beginning of this line
            fseek(inptr, -1 * bi.biWidth * sizeof(RGBTRIPLE), SEEK_CUR);
        }
        //use fseek to go to the next line and skip padding if any
        fseek(inptr, bi.biWidth * sizeof(RGBTRIPLE) + paddingread, SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}