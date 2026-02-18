//**************************** HexDump ****************************************
//  Copyright (c) 2026 Trenser 
//  All Rights Reserved 
//***************************************************************************** 
// 
// Summary    : Contains the declaration of supporting function of HexDump
// Note       : 
// Author     : Kavin M
// Date       : 12.02.2026
// 
//***************************************************************************** 
 
#ifndef _HEXDUMP_H_ 
#define _HEXDUMP_H_ 
 
//******************************* Include Files ******************************* 
#include <stdio.h>
#include <ctype.h> // for isprint function
#include "Main.h"
//******************************* Global Types ******************************** 
#define DEFAULT_SIZE 2
#define DEFAULT_WIDTH 16
#define DEFAULT_OFFSET 0
#define LINE_MAX 120
#define DEFAULT_INDEX 1


// error conditions
#define NULL_CHECK 1
#define FSEEK_ERROR 2
#define FREAD_ERROR 3


typedef struct __sLineConfig
{
    uint8 ucSize;
    uint8 ucWidth;
    uint32 ulOffset;
    uint8 ucDataRead[LINE_MAX];
} _sLineConfig;
//***************************** Global Constants ****************************** 
 
//***************************** Global Variables ****************************** 
 
//**************************** Forward Declarations *************************** 
BOOL TotalLengthValidate(uint8 ucWidth, uint8 ucSize);
uint8 HexDump(_sLineConfig *LineData, FILE *pFile);
void HelpDisplay(char *pcExecutableName);

#endif // _HEXDUMP_H_ 
// EOF 