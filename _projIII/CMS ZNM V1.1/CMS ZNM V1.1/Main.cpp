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
	char Mode = '0';
	
	printf("Coded Messaging System v1.1\n\nPress 1 for Sending mode\nPress 2 for Receiving mode\nPress q to quit\n>");
	Mode = getch();

	switch(Mode)
	{
		case '1' :
		{
			sendmenu();
			break;
		}
		case '2' :
		{
			recmenu();
			break;
		}
	}
}