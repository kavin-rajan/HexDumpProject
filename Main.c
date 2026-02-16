//**************************** HexDump ****************************************
//  Copyright (c) 2026 Trenser 
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
#include <stdlib.h>
#include <getopt.h>
#include "Main.h"
#include "HexDump.h"
//******************************* Local Types ********************************* 
 
//***************************** Local Constants ******************************* 
const struct option sLongOptions[] = {
    {"width",     required_argument, NULL, 'w'},
    {"size",      required_argument, NULL, 's'},
    {"offset",    required_argument, NULL, 'o'},
    {"help",      no_argument,       NULL, 'h'},
    {NULL, 0, NULL, 0}
};
//***************************** Local Variables ******************************* 
 
//****************************** Local Functions ******************************

//******************************.FUNCTION_HEADER.****************************** 
//Purpose : Main function for HexDump
//Inputs  : Filename, width, size, offset 
//Outputs : 
//Return  : Validates input and displays HexValue
//Notes   :
 
//***************************************************************************** 
int main(int argc, char *argv[])
{
    // local variables
    FILE* pFile;
    char* cpFileName;

    LINE_CONFIG LineData;
    uint8 ucStatus = 0;

    // Initialize default value for line
    LineData.ucSize = DEFAULT_SIZE;
    LineData.ucWidth = DEFAULT_WIDTH;
    LineData.ulOffset = DEFAULT_OFFSET;
    
    uint32 ulArguments;

    // Get optional inputs Width, offset, size
    while ((ulArguments = getopt_long(argc, argv, "w:s:o:h", sLongOptions, NULL)) != GETOPT_END)
    {
        switch (ulArguments)
        {
        case 's':
            // Get size input
            LineData.ucSize = atoi(optarg);
            break;
        case 'w':
            // Get width input
            LineData.ucWidth = atoi(optarg);
            break;
        case 'o':
            // Get offset input
            LineData.ulOffset = atoi(optarg);
            break; 
        case '?': 
            /* FALL-THRU */           
        case 'h':
            HelpDisplay(argv[0]);
            return EXIT_FAILURE;
            break;
        default:
            printf("Unexpected error in option parsing.\n");
            return EXIT_FAILURE;
            break;
        }
    }

    // get the file name
    // getopt moves all non-option arguments to the end
    if (optind < argc)
    {
        cpFileName = argv[optind];
    }
    else
    {
        printf("File name is mandatory!\n");
        HelpDisplay(argv[0]);
        return EXIT_FAILURE;
    }

    // check the validity of Total line length based on input width and size
    if (BufferWidthValidate(LineData.ucWidth, LineData.ucSize))
    {
        // Error in TotalLength input exit!!
        return EXIT_FAILURE;
    }

    // Open and validate the entered file name
    pFile = fopen(cpFileName, "rb");
    if (NULL == pFile)
    {
        printf("Error while opening %s or File does not exist!\n", cpFileName);
        return EXIT_FAILURE;
    }

    // HexDump function call
    HexDump(&LineData, pFile, &ucStatus);

    printf("\n");
    fclose(pFile);
    return 0;
}
  
// EOF 
