//**************************** HexDump ****************************************
//  Copyright (c) 2021 Trenser 
//  All Rights Reserved 
//***************************************************************************** 
// 
// File    : Main.c 
// Summary : Contains the main function of hexdump.
// Note    : 
// Author  : Kavin M
// Date    : 12.02.2026
// 
//***************************************************************************** 
 
//******************************* Include Files ******************************* 
#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include "HexDump.h"
//******************************* Local Types ********************************* 
 
//***************************** Local Constants ******************************* 
 
//***************************** Local Variables ******************************* 
 
//****************************** Local Functions ****************************** 
int main(int argc, char *argv[])
{
    // local variables
    unsigned char* ucpFileName;
    unsigned char ucBufferVariableSize = DEFAULT_SIZE;
    unsigned char ucBufferVariableWidth = DEFAULT_WIDTH;
    unsigned char ucBufferVariableOffset = DEFAULT_OFFSET;
    unsigned char ucBufferVariable[MAXBUFFER_SIZE];
    unsigned long ulArguments;

    static struct option LONG_OPTIONS[] = {
        {"width",     required_argument, 0, 'w'},
        {"size",      required_argument, 0, 's'},
        {"offset",    required_argument, 0, 'o'},
        {"help",      no_argument,       0, 'h'},
        {0, 0, 0, 0}
    };
    // get the file name
    ucpFileName = argv[1];

    // Get optional inputs Width, offset, size
    while ((ulArguments = getopt_long(argc, argv, "w:s:o:h:", LONG_OPTIONS, NULL)) != -1)
    {
        switch (ulArguments)
        {
            case 's':
                // Get size input
                ucBufferVariableSize = atoi(optarg);
                break;
            case 'w':
                // Get width input
                ucBufferVariableWidth = atoi(optarg);
                break;
            case 'o':
                // Get offset input
                ucBufferVariableOffset = atoi(optarg);
                break; 
            case '?': 
                /* FALL-THRU */           
            case 'h':
                printf("Usage: %s filename [--size|-o <size>] "
                    "[--width|-w <width>] [--offset|-w <offset>] "
                    "[--help|-h]\n", argv[0]);
                break;
            default:
                abort(); // Should not happen
        }
    }

    FILE* pFile;
    // Open and validate the entered file name
    pFile = fopen(ucpFileName, "rb");
    if (pFile == NULL)
    {
        printf("File doesn't exist\n");
        printf("Usage: %s filename [--size|-o <size>] "
            "[--width|-w <width>] [--offset|-w <offset>] "
            "[--help|-h]\n", argv[0]);
        return 1;
    }
    
    // Validate BufferVariableWidth
    if (BufferWidthValidate(ucBufferVariableWidth, ucBufferVariableSize))
    {
        // Error in BufferSize input exit!!
        return 1;
    }

    // Hex value print function call
    HexValuePrint(
        &ucBufferVariable[0], 
        ucBufferVariableWidth, 
        ucBufferVariableSize, 
        ucBufferVariableOffset, 
        pFile);

    printf("\n");
    fclose(pFile);
    return 0;
}
  
// EOF 
