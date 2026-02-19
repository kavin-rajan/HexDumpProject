//**************************** HexDump **************************************** 
//  Copyright (c) 2026 Trenser 
//  All Rights Reserved 
//***************************************************************************** 
// 
// File     : Hexdump.c 
// Summary  : Contains the main hexdump and its supporting functions
// Note     :
// Author   : Kavin M
// Date     : 12.02.2026
// 
//***************************************************************************** 
 
//******************************* Include Files ******************************* 
#include "HexDump.h"

//******************************* Local Types ********************************* 
 
//***************************** Local Constants ******************************* 
 
//***************************** Local Variables ******************************* 

//****************************** Local Functions ****************************** 

//******************************.FUNCTION_HEADER.****************************** 
//Purpose : To check if the given Total length of characters exeeds 120.
//Inputs  : ucWidth: width of line. ucSize: Size of a word 
//Outputs :
//Return  : FALSE when TotalLength greater than LINE_MAX 
//          TRUE otherwise
//Notes   : TotalLength = ucWidth * ucSize      
 
//*****************************************************************************
BOOL TotalLengthValidate(uint8 ucWidth, uint8 ucSize)
{
    // Check Total length validtity
    // TotalLength = ucWidth * ucSize
    if (((ucWidth * ucSize) > LINE_MAX))
    {
        printf("Total length of the line not in valid range 0 to %d!!\n",
             LINE_MAX);
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}

//******************************.FUNCTION_HEADER.******************************
//Purpose : Prints the Hex data
//Inputs  : psLineData: pointer to a struct that contains input format of line. 
//          pFile: pointer to file to where hex data is stored.
//Outputs :
//Return  : NULL_CHECK: if any pointer argument is NULL
//          FSEEK_ERROR: if any error occurs while function call fseek
//          FREAD_ERROR: if any error occurs while function call fread
//          EXIT_SUCCESS: while no error during execution
//Notes   :
//***************************************************************************** 
uint8 HexDump(_sLineConfig *psLineData, FILE *pFile)
{
    // NULL Check
    if ((NULL == psLineData) || (NULL == pFile))
    {
        return NULL_CHECK;
    }

    // Local variables declaration
    uint32 ulNumberOfCharRead = 0;
    uint16 unLineNumber = DEFAULT_INDEX;
    uint32 ulMaxLineLength = (uint32)psLineData->ucWidth * (uint32)psLineData->ucSize;
    uint32 i = 0;
    uint16 unCounter = 0;

    // Jump to the offset location
    if (fseek(pFile, psLineData->lOffset, SEEK_SET) != 0)
    {
        // error handle when the offset is negative
        return FSEEK_ERROR;
    }

    ulNumberOfCharRead = fread(&psLineData->ucDataRead[0], 
                         sizeof(uint8),
                         ulMaxLineLength, pFile);

    while (ulNumberOfCharRead > 0)
    {
        // fread error check
        if (ulNumberOfCharRead < ulMaxLineLength)
        {
            // Check if an error occured
            if (ferror(pFile))
            {
                return FREAD_ERROR;
            }

        }
        
        // Print the Line number
        printf("%04d|    ", unLineNumber);

        // iterate through the each characters that are read
        for (i = 0; i < ulMaxLineLength; i++)
        {
            if (i < (ulNumberOfCharRead * psLineData->ucSize))
            {
                // Print the read value
                printf("%02x", psLineData->ucDataRead[i]);
            }
            else
            {
                // padding for short values at the end
                printf("  ");
            }
            
            unCounter ++;
            if (unCounter == psLineData->ucSize)
            {
                // Print a space for width
                printf(" ");

                // Reset the counter
                unCounter = 0;
            }
        }

        // Print its ascii value
        printf("     |");
        for (i = 0; i < ulNumberOfCharRead; i++)
        {
            printf("%c", isprint(psLineData->ucDataRead[i]) ?
                                 psLineData->ucDataRead[i]: '.');
        }

        printf("\n");
        unLineNumber ++;

        ulNumberOfCharRead = fread(&psLineData->ucDataRead[0],
                             sizeof(uint8),
                             ulMaxLineLength, pFile);
    }
    return EXIT_SUCCESS;
}

//******************************.FUNCTION_HEADER.****************************** 
//Purpose : To display help.
//Inputs  : pcExecutableName: Executable name
//Outputs : 
//Return  : None
//Notes   :
//*****************************************************************************
void HelpDisplay(char *pcExecutableName)
{
    printf("Usage: %s filename [--size|-s <size>] "
    "[--width|-w <width>] [--offset|-o <offset>] "
    "[--help|-h]\n", pcExecutableName);
}
// EOF 




 

