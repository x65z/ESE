// _projV_readfile.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <math.h> 

void main()
{
	char szBuf[43];
	//char OBuf[50]; //output buf
	unsigned long long iC = 0;
	int c = 0;
	int iX1;
	int iY1;

	FILE * pF;
	//printf("%d", "'");
	pF = fopen("projcont.txt", "r");


	while(c != EOF)
	{
		c= fgetc(pF);

		if( c != 39 && c != 44 && c != 91 && c != 93 ) 
		{
			szBuf[iC] = c;
			iC++;
		}

	}
	szBuf[iC] = NULL;
	printf("Controller: X1 Y1 X2 Y2 LT RT \n");
	puts(szBuf);
	printf("\n");
	
	/* Was going to convert szBuf to Obuf for Alex's code, leaving this just in case
	if (szBuf[0] == 45) //-
	{

	}
	*/


	
	while(1);
}

