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
//Inputs  : ucWidth:width of line, ucSize:Size of a word 
//Outputs :
//Return  : returns the validtiy of the total length given.  
//Notes   : TotalLength = ucWidth * ucSize      
 
//*****************************************************************************
BOOL BufferWidthValidate(uint8 ucWidth, uint8 ucSize)
{
    // Check Total length validtity
    // TotalLength = ucWidth * ucSize
    if (((ucWidth * ucSize) >= LINE_MAX))
    {
        printf("Total length of the line not in valid range 0 to %d!!\n",
             LINE_MAX);
        return INVALID;
    }
    else
    {
        return VALID;
    }
}

//******************************.FUNCTION_HEADER.******************************
//Purpose : Prints the Hex data
//Inputs  : pLineData: input format of the line
//Outputs : ucStatus: status of hexdump
//Return  :
//Notes   :
//***************************************************************************** 
void HexDump(LINE_CONFIG* pLineData, FILE* pFile, uint8* ucStatus)
{
    // NULL Check
    if ((NULL == pLineData) || (NULL == pFile))
    {
        printf("pointer is NULL!\n");
        *ucStatus = NULL_CHECK;
        return;
    }

    // Local variables declaration
    uint8 ucNumberOfCharRead = 0;
    uint16 unLineNumber = DEFAULT_INDEX;
    uint16 unMaxLineLength = (pLineData->ucWidth * pLineData->ucSize);
    uint16 idx = 0;

    // Jump to the offset location
    if (fseek(pFile, pLineData->ulOffset, SEEK_SET) != 0)
    {
        printf("error in the input offset\n");
        *ucStatus = FSEEK_ERROR;
        return;
    }

    ucNumberOfCharRead = fread(&pLineData->ucDataRead[0], 
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
                *ucStatus = FSEEK_ERROR;
                return;
            }

        }

        // Local variables
        uint16 unCounter = 0;

        // Print the Line number
        printf("%04d|    ", unLineNumber);

        // iterate through the each characters that are read
        for (idx = 0; idx < unMaxLineLength; idx++)
        {
            if (idx < (ucNumberOfCharRead * pLineData->ucSize))
            {
                // Print the read value
                printf("%02x", pLineData->ucDataRead[idx]);
            }
            else
            {
                // padding for short values at the end
                printf("  ");
            }
            
            unCounter ++;
            if (unCounter == pLineData->ucSize)
            {
                // Print a space for width
                printf(" ");

                // Reset the counter
                unCounter = 0;
            }
        }

        // Print its ascii value
        printf("     |");
        for (idx = 0; idx < ucNumberOfCharRead; idx++)
        {
            printf("%c", isprint(pLineData->ucDataRead[idx]) ?
                                 pLineData->ucDataRead[idx]: '.');
        }

        printf("\n");
        unLineNumber++;

        ucNumberOfCharRead = fread(&pLineData->ucDataRead[0],
                             sizeof(uint8),
                             unMaxLineLength, pFile);
    }
}

//******************************.FUNCTION_HEADER.****************************** 
//Purpose : To display help.
//Inputs  : executable file name.
//Outputs : displays the help for HexDump executable file. 
//Return  :
//Notes   :
//*****************************************************************************
void HelpDisplay(char* cpFileName)
{
    printf("Usage: %s filename [--size|-s <size>] "
    "[--width|-w <width>] [--offset|-o <offset>] "
    "[--help|-h]\n", cpFileName);
}
// EOF 




 

