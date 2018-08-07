/*
Name: Marium Kanwal				Date: 11/16/2016
Program: assignment 4 Question 2a
Tested: question 1b
And this program is tested by question 2b: Zack Henkusens

ENCODING DONE BY MARIUM
DECODING DONE BY NIV
Testing by Zack, modified mainline, added get from file
	-Added ability to compress text files

*/

#include "Header.h"

void main()
{
	char iBuf[SLENGTH];
	char oBuf[SLENGTH];
	char deBuf[SLENGTH];
	int InLen=0; 
	int flag = 0;
	//int iOutMax=0;

	printf("Read from file (y/n)? Press a to decode compressed.txt\n"); //Added by Zack
    scanf("%s",&iBuf);
	
	if (iBuf[0] == 'y')
	{
		flag = GetMessageFromFile(iBuf);
		if (flag == 0)
		{
			//puts(iBuf); //Debug
			InLen = strlen(iBuf);
			RLEncode(iBuf, InLen, oBuf);
			//puts(oBuf); //Debug
			WriteToFile(oBuf);
			printf("\nWrote to file.");
		}
		else
		{
			printf("Error, problem reading file");
		}
	}
	else if (iBuf[0] == 'a')
	{
		flag = GetMessageFromFileCompressed(iBuf);
		if (flag == 0)
		{
			//puts(iBuf); //Debug
			printf("\nRead file.");
			InLen = strlen(iBuf);
			RLDecode(iBuf, InLen, oBuf);
			//puts(oBuf); //Debug
			WriteToFileu(oBuf);
			printf("\nWrote to file.");
		}
		else
		{
			printf("Error, problem reading file");
		}
	}
	else
	{
		printf("\nEnter message.\n");
		gets(iBuf);
		gets(iBuf);
		InLen = strlen(iBuf);

		RLEncode(iBuf, InLen, oBuf);
		printf("Output to Buffer:\n");
		puts(oBuf); //debug

		InLen = strlen(oBuf);

		RLDecode(oBuf, InLen, deBuf);
		
	    printf("\nDecoded output is:\n");
		puts(deBuf); //debug
		
	}
	getch();
}
