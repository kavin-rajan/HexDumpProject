//**************************** HexDump ****************************************
//  Copyright (c) 2021 Trenser 
//  All Rights Reserved 
//***************************************************************************** 
// 
// Summary    : Contains the declaration of supporting function of HexDump
// Note       : 
// 
//***************************************************************************** 
 
#ifndef _HEXDUMP_H_ 
#define _HEXDUMP_H_ 
 
//******************************* Include Files ******************************* 

//******************************* Global Types ******************************** 
#define DEFAULT_SIZE 2
#define DEFAULT_WIDTH 16
#define DEFAULT_OFFSET 0
#define MAXBUFFER_SIZE 120
#define LINENUMBER_STARTVALUE 1
//***************************** Global Constants ****************************** 
 
//***************************** Global Variables ****************************** 
 
//**************************** Forward Declarations *************************** 
unsigned char BufferWidthValidate(
    unsigned char BufferVariableWidth, 
    unsigned char BufferVariableSize);
void HexValuePrint(
    unsigned char* BufferVariable, 
    unsigned char ucBufferVariableWidth, 
    unsigned char BufferVariableSize, 
    unsigned char ucBufferVariableOffset, 
    FILE* pFile);

#endif // _HEXDUMP_H_ 
// EOF 