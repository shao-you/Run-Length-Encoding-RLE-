#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    FILE *inFile;
    FILE *outFile;
    unsigned char ch, prevch;
    unsigned char state = 0;
    unsigned char cnt = 0;

#if 1
    //compress
    inFile = fopen("input.bin", "rb");
    outFile = fopen("compress.bin", "wb");

    if (NULL == inFile) {
        printf("inFile can't be opened \n");
    }
    if (NULL == outFile) {
        printf("outFile can't be opened \n");
    }

    while (fread(&ch, 1, 1, inFile)) 
    {
        if (state == 0)
        {
            state = 1;
            prevch = ch;
            fwrite(&ch, 1, 1, outFile);
        }
        else if (prevch == ch)
        {
            state++;
            if (state == 2)
            {
                fwrite(&ch, 1, 1, outFile);
            }
            else if (state == 0xFF)
            {
                state -= 2;
                fwrite(&state, 1, 1, outFile);
                state = 0;  
            }
        }
        else if (state >= 2)
        {
            state -= 2;
            fwrite(&state, 1, 1, outFile);
            state = 1;
            prevch = ch;
            fwrite(&ch, 1, 1, outFile);
        }
        else //state == 1
        {
            prevch = ch;
            fwrite(&ch, 1, 1, outFile);
        }
    }
    if (state >= 2) //for the final check
    {
        state -= 2;
        fwrite(&state, 1, 1, outFile);
    }
    fclose(inFile);
    fclose(outFile);
    cout <<"======= 1.\n";
#endif

#if 1
    //decompress
    state = 0;
    inFile = fopen("compress.bin", "rb");
    outFile = fopen("decompress.bin", "wb");
    
    while (fread(&ch, 1, 1, inFile)) 
    {
        if (state < 2)
        {
            if (state == 0)
            {
                state = 1;
                prevch = ch;
            }
            else if (prevch == ch)
            {
                state = 2;
            }
            else //state == 1
            {
                prevch = ch;
            }
            fwrite(&ch, 1, 1, outFile);
        }
        else
        {
            state = 0;
            while (ch--)
            {
                fwrite(&prevch, 1, 1, outFile);
            }
        }  
    }
    fclose(inFile);
    fclose(outFile);
    cout <<"======= 2.\n";
#endif
    return 0;
}