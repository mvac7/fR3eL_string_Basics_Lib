/* =============================================================================
# Example01

- Version: 1.0
- Architecture: MSX
- Format: 8K ROM
- Programming language: C and Z80 assembler
- Compiler: SDCC 4.4

## Description:
	Simple example of the string_Basics Library (fR3eL Project)
============================================================================= */
#include "textmode_MSX.h"
#include "string_Basics.h"

const char text01[] = "Example string_Basics Lib";
const char text02[] = "Press a key to continue";
const char text03[] = "Length:";
const char string1[] = ", consectetur adipiscing elit.";


void main(void)
{	
	char stringLine[40];
	char text[60];	
	char stringLength;
	
	COLOR(WHITE,DARK_BLUE,LIGHT_BLUE);
	WIDTH(40);
	SCREEN0();
	
	STRING(stringLine,40,'-');
	
	PrintLN(text01);
	PRINT(stringLine);
	
	PrintLN(">StrCopy(text,\"Lorem ipsum dolor sit amet\")");
	StrCopy(text,"Lorem ipsum dolor sit amet");
	PRINT("text=");
	PrintLN(text);
	
	stringLength = StrLength(text);	
	PRINT(text03);
	PrintNumber(stringLength);
	
	PrintLN("\n");
	
	PrintLN(">StrConcatenate(text,string1)");
	PRINT("string1=");
	PrintLN(string1);
	StrConcatenate(text,string1);		
	PRINT("text=");
	PrintLN(text);
	
	stringLength = StrLength(text);	
	PRINT(text03);
	PrintNumber(stringLength);
	
	PrintLN("\n");
	PRINT(text02);    
// execute BIOS CHGET - One character input (waiting)
__asm call 0x009F __endasm;	
}
