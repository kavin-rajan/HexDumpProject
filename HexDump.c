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
//Inputs  : ucWidth: width of line, ucSize: Size of a word 
//Outputs :
//Return  : TRUE when TotalLength greater than LINE_MAX FALSE otherwise
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
        return TRUE;
    }
    else
    {
        return FALSE;
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
        printf("pointer is NULL!\n");
        return NULL_CHECK;
    }

    // Local variables declaration
    uint8 ucNumberOfCharRead = 0;
    uint16 unLineNumber = DEFAULT_INDEX;
    uint16 unMaxLineLength = (uint16)(psLineData->ucWidth * psLineData->ucSize);
    uint16 i = 0;

    // Jump to the offset location
    if (fseek(pFile, psLineData->ulOffset, SEEK_SET) != 0)
    {
        printf("error in the input offset\n");
        return FSEEK_ERROR;
    }

    ucNumberOfCharRead = fread(&psLineData->ucDataRead[0], 
                         sizeof(uint8),
                         unMaxLineLength, pFile);

    while (ucNumberOfCharRead > 0)
    {
        // fread error check
        if (ucNumberOfCharRead < unMaxLineLength)
        {
            // Check if an error occured
            if (ferror(pFile))
            {
                printf("error while reading file!!\n");
                return FREAD_ERROR;
            }

        }

        // Local variables
        uint16 unCounter = 0;

        // Print the Line number
        printf("%04d|    ", unLineNumber);

        // iterate through the each characters that are read
        for (i = 0; i < unMaxLineLength; i++)
        {
            if (i < (ucNumberOfCharRead * psLineData->ucSize))
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
        for (i = 0; i < ucNumberOfCharRead; i++)
        {
            printf("%c", isprint(psLineData->ucDataRead[i]) ?
                                 psLineData->ucDataRead[i]: '.');
        }

        printf("\n");
        unLineNumber++;

        ucNumberOfCharRead = fread(&psLineData->ucDataRead[0],
                             sizeof(uint8),
                             unMaxLineLength, pFile);
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




 

