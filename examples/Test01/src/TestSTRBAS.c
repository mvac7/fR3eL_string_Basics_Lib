/* =============================================================================
# TestSTRBAS

- Version: 1.2 (12/01/2025)
- Author: mvac7/303bcn
- Architecture: MSX
- Format: 8K ROM
- Programming language: C and Z80 assembler
- Compiler: SDCC 4.4

## Description:
Test string_Basics Library
 
## History of versions: (dd/mm/yyyy)
- v1.2 (12/01/2025) update to SDCC (4.1.12) Z80 calling conventions
- v1.1 (26/07/2018)
- v1.0 (22/04/2016)     
============================================================================= */

#include "../include/newTypes.h"
#include "../include/msxBIOS.h"
#include "../include/msxSystemVariables.h"

#include "../include/textmode_MSX.h"
#include "../include/string_Basics.h"



// ---------------------------------------------------------------------------- Labels
#define  HALT __asm halt __endasm   //wait for the next interrupt



// ---------------------------------------------------------------------------- Declaration of functions
void WAIT(unsigned int cicles);
char INKEY(void);

void test(void);

void PrintBool(boolean bvalue);
void PrintHeader(void);
void ShowPressKey(void);


//void INPUT(char* string);
//void INPUTL(char* string, char length);





// ---------------------------------------------------------------------------- Constants
const char txtAppAbout[] = "Test string_Basics Library      page:";
const char txtPressKey[] = "Press any key to continue";
const char     txtLine[] = "----------------------------------------";
//const char endChar[] = "\xdd";




// ---------------------------------------------------------------------------- Global Variables
char testpage;



// ---------------------------------------------------------------------------- Definition of functions
void main(void)
{
	//init global variables
	testpage=1;
	//END init
	
	COLOR(GRAY,DARK_BLUE,DARK_GREEN);      
	WIDTH(40);
	SCREEN0();	
	
	test();
	
	CLS();
	PRINT("END TEST");
	WAIT(120);
}




/* =============================================================================
WAIT
Description:	Generates a pause in the execution of n interruptions.
Input:			[unsigned int]  cicles number (VBLANKs)
				(Note: PAL: 50=1second. ; NTSC: 60=1second.)
============================================================================= */
void WAIT(unsigned int cicles)
{
	unsigned int i;
	for(i=0;i<cicles;i++) HALT;
}



/* =============================================================================
INKEY
Description: 
		Waits for a key press and returns its value
Input:	-
Output:	[char] key code
============================================================================= */
char INKEY(void) __naked
{
__asm   
	jp  BIOS_CHGET
__endasm;
}



// TEST ###############################################################
void test(void)
{
	char text1[60] = "";
	char text2[60] = "";
	char string1[] = "Lorem ipsum dolor sit amet";
	char string2[] = ", consectetur adipiscing elit.";
	char result;
	boolean resbool;


//------------------------------------------------------------------------------ page 1  
	PrintHeader();

	PRINT("text1=");
	PrintLN(text1);
	PRINT("string1=");
	PrintLN(string1);
	PRINT("string2=");
	PrintLN(string2); 

	//char StrLength(char* string1)
	PrintLN("\n>Test StrLength");
	PRINT("StrLength(string1)=");
	result=StrLength(string1);
	PrintNumber(result);
	PRINT("\nStrLength(string2)=");
	result=StrLength(string2);
	PrintNumber(result);

	//void StrCopy(char* target, char* source)
	PrintLN("\n\n>Test StrCopy(text1,string1)");
	StrCopy(text1,string1);
	PRINT("text1=");
	PrintLN(text1);

	//void StrConcatenate(char* target, char* source)
	PrintLN("\n>Test StrConcatenate(text1,string2)");  
	StrConcatenate(text1,string2);
	PRINT("text1=");
	PrintLN(text1);

	PrintLN("\n>Test StrCompare(string1,string2)");
	PRINT("StrCompare(\"turboR\",\"MSX3\")=");
	resbool = StrCompare("turboR","MSX3");	//must return false
	PrintBool(resbool);

	PRINT("StrCompare(\"TMS9918A\",\"tms9918a\")=");
	resbool = StrCompare("TMS9918A","tms9918a");	//must return false
	PrintBool(resbool);

	PRINT("StrCompare(\"1234567890\",\"1234\")=");
	resbool = StrCompare("1234567890","1234");	//must return false
	PrintBool(resbool);

	PRINT("StrCompare(\"EqU4L\",\"EqU4L\")=");
	resbool = StrCompare("EqU4L","EqU4L");	//must return true
	PrintBool(resbool);


	ShowPressKey();
  
  
//------------------------------------------------------------------------------ page 2
	PrintHeader();

	PRINT("text1=");
	PrintLN(text1);  
	PRINT("text2=");
	PrintLN(text2);  


	//void LEFT(char* target, char* source, char length)
	PrintLN("\n>Test LEFT(target,source,length)");
	PrintLN("LEFT(text2,text1,11)");  
	LEFT(text2,text1,11);  
	PRINT("text2=");
	PrintLN(text2);

	//void RIGHT(char* target, char* source, char rightLength)
	PrintLN("\n>Test RIGHT(target,source,length)");
	PrintLN("RIGHT(text2,text1,16)");  
	RIGHT(text2,text1,16);  
	PRINT("text2=");
	PrintLN(text2);

	//void MID(char* target, char* source, char leftPos, char length)
	PrintLN("\n>Test MID(target,source,leftPos,length)");
	PrintLN("MID(text2,text1,12,14)");  
	MID(text2,text1,12,14);  
	PRINT("text2=");
	PrintLN(text2);

	//char INSTR(char* target, char asciicode, char offset)
	PrintLN("\n>Test INSTR(target,asciicode,offset)");
	PRINT("INSTR(text1,' ',0)=");
	result=INSTR(text1,' ',0);
	PrintNumber(result);
	PRINT("\nINSTR(text1,32,7)=");
	result=INSTR(text1,32,7);
	PrintNumber(result);


	ShowPressKey();
  
//------------------------------------------------------------------------------ page 3
	PrintHeader();

	//void STRING(char* target, char length, char asciicode) 
	PrintLN(">Test STRING(target,length,asciicode)");
	PrintLN("STRING(text1,20,'-')");  
	STRING(text1,20,'-');  
	PRINT("text1=");
	PrintLN(text1);
  
/* 
	void SPACE(char* target, char length)
	PRINT("\n\n>Test SPACE(target,length)");
	PRINT("\nSPACE(text2,10)");  
	SPACE(text2,10);  
	PRINT("\nResult>text2=");
	PRINT(text2);
	PRINT("<");
*/  
  
	ShowPressKey();
}



void PrintBool(boolean bvalue)
{
	if(bvalue) PrintLN("true"); 
	else PrintLN("false"); 	
}



void PrintHeader(void)
{
	CLS();
	PRINT(txtAppAbout);
	PrintFNumber(testpage++,32,1);
	PRINT("/3");
	PRINT(txtLine);
}



void ShowPressKey(void)
{
	LOCATE(0,23);
	PRINT(txtPressKey);
	INKEY();	
}



/*void INPUT(char* string)
{
  INPUTL(string,32);
}*/



/*void INPUTL(char* string, char length)
{
  //char string[16];
  char aKey=0;
  char size=0;
  
  KillBuffer();
  
  //length = strlen(string);
  
  while(1)
  {
    aKey = INKEY();
    if (aKey==13) break;
  
    if (aKey==8 && size>0)//BS
    {
      size--;
      //bchput(8); //32
      bchput(127); //del
      string[size]=32; 
    }
//    if (aKey==29 && size>0)//left arrow
//    {            
//      size--;
//      bchput(29); //32
//      string[size]=32;
//    }
//    if (aKey==28 && size<length)//right arrow
//    {            
//      size++;
//      bchput(28);
//      string[size]=32;
//    }
    if(aKey>31 && aKey<123 && size<length)
    {
      //if (aKey>96) aKey-=32; //lowercase
      string[size]=aKey;
      bchput(aKey);
      size++;
    }  
  }
  string[size]=0; //END mark

  return;
}*/