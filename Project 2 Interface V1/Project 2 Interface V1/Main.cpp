//Interface Proj Interface v1  Main Zack H
//Oct. 30, 2016
//Modified assignment 2 that uses trees
using namespace std;
#include "Header.h"


void main()
{
	char Buf[MLENGTH + 1];
	int iText = 0;
	int iAud = 0;
	int iLen = MLENGTH;
	int flag = 0;
	int memflag = 0;//Is there anything stored in memory?
	srand((unsigned)time(0)); //Seeds random # generator
	char Uin = '0';
	

	while (Uin != 'q')
	{
		system("cls");
		printf("Coded Messaging System Alpha v.04\n\nYou have %d text message", iText);
		if (iText != 1)
		{
			printf("s"); //adds 's' to 'message'
		}
		printf(" and %d audio message", iAud);
		if (iAud != 1)
		{
			printf("s"); //adds 's' to 'message'
		}
		printf("\n\nPress 1 for text options\nPress 2 for audio options\nPress 3 to save to file\nPress 4 to load from file\nPress q to quit\n> ");
		Uin = getch();

		switch(Uin)	
		{
			case '1' :	
			{
				iText = iText + textmenu();
				break;
			}
			case '2' : 
			{
				iAud = iAud + audmenu();
				break;
			}
		}
	}
}