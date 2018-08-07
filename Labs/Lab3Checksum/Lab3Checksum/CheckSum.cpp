//Zack H Lab 3 Checksum

#include "Checksum.h"

unsigned int Checksum( void *buf, int iBufLen, CHECKSUM iType )
{
	unsigned char *sbit;
	unsigned short *lbit;
	int sum = 0;

	switch ( iType ) {
		case CHK_8BIT :
			sbit = (unsigned char*)buf;
			//printf("\nchar: %c \n\n", sbit); //debug
			for(int i=0; i<iBufLen; i++)
			{
				sum += *(sbit++);
			}
			return (sum % 0xff);
			 
		case CHK_16BIT :
			lbit = (unsigned short *)buf;
			for(int i=0; i<iBufLen; i++)
			{
				sum += *(lbit++);
			}
			return (sum % 0xffff);

		case CHK_ERROR: return 2;
	}
			
}