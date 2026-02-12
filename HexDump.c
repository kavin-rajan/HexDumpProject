//**************************** HexDump **************************************** 
//  Copyright (c) 2021 Trenser 
//  All Rights Reserved 
//***************************************************************************** 
// 
// File     : Hexdump.c 
// Summary  : Contains the main hexdump and its supporting functions
// Author   : Kavin M
// Date     : 12.02.2026
// 
//***************************************************************************** 
 
//******************************* Include Files ******************************* 
#include <stdio.h>
#include "HexDump.h"
#include <ctype.h> // for isprint function
//******************************* Local Types ********************************* 
 
//***************************** Local Constants ******************************* 
 
//***************************** Local Variables ******************************* 

//****************************** Local Functions ****************************** 

//******************************.FUNCTION_HEADER.****************************** 
//Purpose : To validate the input BufferWidth
//Inputs  :  Width of bufferVariable
//Outputs : 
//Return  :  Validity of the Buffer size. 1 -> invalid value, 0 -> valid value               
 
//********************************************************************************** 
unsigned char BufferWidthValidate(
    unsigned char ucBufferVariableWidth, 
    unsigned char ucBufferVariableSize)
{
    // Check for the validity of Buffer 
    if (((ucBufferVariableWidth * ucBufferVariableSize) >= MAXBUFFER_SIZE) || 
    (ucBufferVariableWidth < 0) ||
    (ucBufferVariableSize < 0))
    {
        printf("Total length of the line not in valid range 0 to %d!!\n", MAXBUFFER_SIZE);
        return 1;
    }
    else
    {
        return 0;
    }
}

//******************************.FUNCTION_HEADER.****************************** 
//Purpose : To validate the input BufferSize
//Inputs  : Size of bufferVariable
//Outputs : Prints the HexValues and ASCII as output 
//********************************************************************************** 
void HexValuePrint(
    unsigned char* ucBufferVariable, 
    unsigned char ucBufferVariableWidth, 
    unsigned char ucBufferVariableSize, 
    unsigned char ucBufferVariableOffset, 
    FILE* pFile)
{
    unsigned char ucNumberOfCharRead;
    unsigned short usLineNumber = LINENUMBER_STARTVALUE;
    unsigned short usMaxWordLength = (ucBufferVariableWidth * ucBufferVariableSize);

    // Jump to the offset location
    if (fseek(pFile, ucBufferVariableOffset, SEEK_SET) != 0)
    {
        printf("error in the input offset");
    }

    ucNumberOfCharRead = fread(ucBufferVariable, sizeof(unsigned char), usMaxWordLength, pFile);

    while (ucNumberOfCharRead > 0)
    {
        // Local variables
        unsigned short usCounter=0;

        // Print the Line number
        printf("%04d:    ", usLineNumber);

        // Print the hex values
        for (int itr = 0; itr < usMaxWordLength; itr++)
        {
            if (itr < (ucNumberOfCharRead * ucBufferVariableSize))
            {
                // Print the read value
                printf("%02x", ucBufferVariable[itr]);
            }
            else
            {
                // padding for short values at the end
                printf("  ");
            }
            
            usCounter ++;
            if (usCounter == ucBufferVariableSize)
            {
                // Print a space for width
                printf(" ");

                // Reset the counter
                usCounter = 0;
            }
        }

        // Print its ascii value
        printf("     |");
        for (int itr = 0; itr < ucNumberOfCharRead; itr++)
        {
            printf("%c", isprint(ucBufferVariable[itr]) ? ucBufferVariable[itr]: '.');
        }

        printf("\n");
        usLineNumber++;

        ucNumberOfCharRead = fread(ucBufferVariable, sizeof(unsigned char), usMaxWordLength, pFile);

    }
}
 

// EOF 




 

