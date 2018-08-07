#include "Header.h"

int GetMessageFromFile(char szBuf[]) //Zack
{
	char Flag = 'a'; //Var is used to detect double %
	int iEntries = 0;
	//int iLook = rand() % 1141; //Finds random entry to look for
	unsigned long long iC = 0;
	int c = 0;

	FILE * pF;
	pF = fopen("FortuneCookies.txt", "r");  //***FILE NAME HERE***
	if (pF != NULL)
	{
		c = fgetc(pF);

		while (c != EOF)
		{
		
			
				//printf("%d\n", iC);//Debug
				szBuf[iC] = c;
				
				iC++;

			
			c = fgetc(pF);
		}
		szBuf[iC] = NULL;
		fclose(pF);
		return(0);
	}
	
	return(1);

}

int GetMessageFromFileCompressed(char szBuf[]) //Zack
{
		char Flag = 'a'; //Var is used to detect double %
	int iEntries = 0;
	//int iLook = rand() % 1141; //Finds random entry to look for
	unsigned long long iC = 0;
	int c = 0;

	FILE * pF;
	pF = fopen("Compressed.txt", "r");  //***FILE NAME HERE***
	if (pF != NULL)
	{
		c = fgetc(pF);

		while (c != EOF)
		{
		
			
				//printf("%d\n", iC);//Debug
				szBuf[iC] = c;
				
				iC++;

			
			c = fgetc(pF);
		}
		szBuf[iC] = NULL;
		fclose(pF);
		return(0);
	}
	
	return(1);
}

int WriteToFile(char szBuf[]) //Zack
{
	char Flag = 'a'; //Var is used to detect double %
	int iEntries = 0;
	//int iLook = rand() % 1141; //Finds random entry to look for
	unsigned long long iC = 0;
	int c = 0;

	FILE * pF;
	pF = fopen("Compressed.txt", "w"); //***FILE NAME HERE***
	if (pF != NULL)
	{
		//c = fgetc(pF);

		fprintf(pF, "%s", szBuf);

		szBuf[iC] = NULL;
		fclose(pF);
		return(0);
	}

	return(1);

}

int WriteToFileu(char szBuf[]) //Zack
{
	char Flag = 'a'; //Var is used to detect double %
	int iEntries = 0;
	//int iLook = rand() % 1141; //Finds random entry to look for
	unsigned long long iC = 0;
	int c = 0;

	FILE * pF;
	pF = fopen("unCompressed.txt", "w"); //***FILE NAME HERE***
	if (pF != NULL)
	{
		//c = fgetc(pF);

		fprintf(pF, "%s", szBuf);

		szBuf[iC] = NULL;
		fclose(pF);
		return(0);
	}

	return(1);

}

void RLEncode( char *iBuf, int InLen, char *oBuf) //Marium
{
	int count = 0;
	int setcount = 1;
	int temp = 255;
	char Temp[3];
	char intTemp[4];
	char flag = 'a';

	oBuf[0] = NULL;
	while(count<InLen)
	{
		if(iBuf[count + 1]==iBuf[count+2])
		{
			flag = 'b';
		}
		if(iBuf[count]==iBuf[count+1] && setcount < 9 && flag =='b')
		{
			setcount++;
			count++;
		}
 
		else
		{
			//printf("\n\nSetcount: %d\n\n", setcount);//debug
			if(setcount>1)
			{

				//printf("%c\\%d",iBuf[count],setcount);//debug
				Temp[0] = iBuf[count];

				Temp[1] = 92;
				Temp[2] = NULL;
				strcat(oBuf, Temp);
				sprintf(intTemp, "%d", setcount);

				strcat(oBuf, intTemp);
			}			
			else
			{
				//printf("%c",iBuf[count]);

				Temp[0] = iBuf[count];
				Temp[1] = NULL;

				strcat(oBuf, Temp);

			}
			flag = 'a';
			setcount=1;
			count++;
		}
	} 
    printf("\n");
	//printf("\Output to Buffer: ");
	//puts(oBuf); //debug
    //getch();
}




void RLDecode(char *iBuf, int InLen, char *oBuf) //Niv
{
	int count = 0;
	int setcount = 1;
	int temp = 255;
	char Temp[3];
	char intTemp[4];
	int i;
	

	oBuf[0] = NULL;												// initilizes the oBuf
	while (iBuf[count] != NULL)									// runs while the compressed string is not null
	{
		if (iBuf[count + 1] == 92)								// Look for a slash to decompress
		{
			Temp[0] = iBuf[count];								// Stores the current letter 
			Temp[1] = NULL;										// terminates the temp string
			for (i = 0; i < (iBuf[count + 2]-48); i++)			// Looks at the number after the slash to know how many times to repeat the letter in the decompressed string
			{
				strcat(oBuf, Temp);								// generates the decompressed string one letter at a time

			}
			count = count + 3;									// assuming one digit compression, this goes to the next letter in the compressed string
		}

		// If no slash is found, then it simply writes the letter into the output string
		else
		{
			Temp[0] = iBuf[count];			Temp[1] = NULL;

			strcat(oBuf, Temp);
			count++;
		}
	}
	
}
 

