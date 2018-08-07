//Algortithms Asignment 1 "Queues" Functions.cpp
//Sept. 28, 2016
//Takes a random message from  an external file, queues in linked list and outputs to screen
//There are 1141 entries
#include "Header.h" 

int GetMessageFromFile(char szBuf[], int iLen)
{
	char Flag = 'a';
	int iEntries = 0;
	int iLook = rand() % 1141; //Finds random entry to look for
	int iC;
	int c = 0;

	FILE * pF;
	pF = fopen("FortuneCookies.txt", "r");
	if (pF != NULL)
	{
		c = fgetc(pF);

		while (c != EOF)
		{
			//printf("%c", c); //debug
			if (c == 37 && Flag == 'a')
			{
				Flag = 'b';
				if (iEntries - 1 == iLook)
				{
					//printf("%d", iC); //debug
					//printf("iC == %d\n", iC); //debug
					if (iC > iLen)
					{
						iC = iLen;
					}
					szBuf[iC] = NULL;
				}
				iEntries++;
				iC = 0;
				//printf("c = %c, Flag = 1\n", c); //debug
			}
			else if (c == 37 && Flag == 'b')
			{
				Flag = 'a';
				//printf("c = %c, Flag = 0\n", c); //debug
			}
			else
			{
				//printf("c = %c ic = %d iEntries = %lu \n", c, iC, iEntries); //debug
				if (iC < (iLen) && (iEntries - 1) == iLook)
				{
					szBuf[iC] = c;
				}
				iC++;

			}
			c = fgetc(pF);
		}
		fclose(pF);
		return(0);
	}
	//printf("Entries: %d", iEntries); //debug
	return(1);

}

