//Zack H Algorithms Lab 4
//Main Outputs vaules to test crc function

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> 
#include <malloc.h>
#include "crc.h"

#define nBytes 10//would usually put this in header but didn't want to modify it
#define crclen 5

void main()
{
	int i = 0;
	crc crc_value;
	unsigned char crcs[5];
	unsigned char buf[nBytes];
	char sbuf[nBytes];
	unsigned int iAlt;
	unsigned char *Bbuf;
	srand((unsigned)time(0)); //Seeds random # generator

	Bbuf = (unsigned char *)calloc(nBytes + crclen + 3, sizeof(unsigned char));

	for(; i < nBytes - 1; i++) //Fills string buf of length nBytes with dec values
	{
		sprintf(sbuf + i, "%d", i + 1);
	}
	
	for(i = 0;  i < nBytes - 1; i++) //Moving contents of sbuf to buf to make comaptible with function
	{
		buf[i] = sbuf[i];
		//printf("%c", buf[i]); debug
	}
	buf[nBytes - 1] = NULL;
	

	crc_value = crcSlow(buf, nBytes);
	printf("\nThe crcSlow of %s is 0x%x\n", buf, crc_value);

	strcpy(Bbuf, nBytes, buf, nBytes); 


	for(i = 0; i < 3; i++)
	{
		iAlt = rand() % (nBytes - 1); //character to edit
		printf("\n%d\n", iAlt);
		buf[iAlt] = '0';
		crc_value = crcSlow(buf, nBytes);
		printf("\nThe crcSlow of %s is 0x%x\n", buf, crc_value);
	}

	while(1){}
}