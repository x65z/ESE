#include "Parity.h"
#include <stdio.h>

PARITY ParityOnBytes( char *buf, int iBufLen )
{ 
	//printf("buf: "); //Debug
	//puts(buf);
	int Count = 0;

	for(int  i = 0; i < iBufLen; i++, buf++) //Counts '1's
	{
		if(*buf == '1')
		{
			Count++;
		}
	}
	if (( Count & 1) == 0)
	{
		return(PAR_EVEN);
	}
	else if (( Count & 0) == 0)
	{
		return(PAR_ODD);
	}
	else
	{
		return(PAR_ERROR);
	}

}

PARITY Parity( unsigned char *buf, int iBuffLen )
{
	int count = 0; //Counts 1s
	unsigned char holder = *buf;
	int i2 = iBuffLen;
	for(int i =0; i < 8; i++) //Checks 8 bits
	{
		
		if (holder & 1 == 1)
		{
			count++;
			//printf("Count: %d\n", count); //debug
		}
		holder >>= 1;
	}
	if (( count & 1) == 0)
	{
		return(PAR_EVEN);
	}
	else if (( count & 0) == 0)
	{
		return(PAR_ODD);
	}
	else
	{
		return(PAR_ERROR);
	}

}