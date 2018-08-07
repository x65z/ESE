//Algortithms Assignment 5 "Hashing" Main Zack H
//Nov. 26, 2016
//Modified assignment 3 that uses hashing
using namespace std;
#include <string.h>
#include "Header.h"
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>


void main()
{
	char Buf[MLENGTH + 1];
	int iLen = MLENGTH;
	char iBuf[SLENGTH]; //For storing entire fortunecookie file
	int InLen=0; 
	int flag = 0;
	int memflag = 0;//Is there anything stored in memory?
	srand((unsigned)time(0)); //Seeds random # generator
	char Uin = '0';

	while (Uin != 'q')
	{
		system("cls");
		printf("Press 1 to insert a message\nPress 2 to read messages\nPress 3 to search messages\nPress 4 to count messages\nPress 5 to determine max tree height\nPress 6 to add 10 random messages\nPress 7 to clear messages\nPress 8 to hash text\nPress q to quit\n> ");
		Uin = getch();

		switch (Uin)
		{
			case '1': //Insert Message
			{
				memflag = 1;
				printf("\nEnter your message\n> ");
				gets(Buf);
				create_node(Buf);
				break;
			}
			case '2': //Print Messages alphabetically
			{
				if (memflag == 1)
				{
					printf("\n\n");
					display_list('1'); //Prints messages
					printf("\nPress any key to continue\n>");
					Uin = getch();
				}
				else
				{
					printf("\nPlease enter a message first.\n");
					printf("\nPress any key to continue\n>");
					Uin = getch();
				}
				break;
			}
			case '3': //search
			{
				if (memflag == 1)
				{
					printf("\nEnter character for search (case sensitive)\n>");
					Uin = getch();
					search(Uin);
					printf("\nPress any key to continue\n>");
					Uin = getch();
				}
				else
				{
					printf("\nPlease enter a message first.\n");
					printf("\nPress any key to continue\n>");
					Uin = getch();
				}
				break;
			}
			case '4': //count
			{
				if (memflag == 1)
				{
					printf("\nThere are %d messages.", count_list('1')); //counts messages
					printf("\nPress any key to continue\n>");
					Uin = getch();
				}
				else
				{
					printf("\nPlease enter a message first.\n");
					printf("\nPress any key to continue\n>");
					Uin = getch();
				}
				break;
			}
			case '5': //Max height
			{
				if (memflag == 1)
				{
					printf("\nMax height is %d nodes.", height_list('1')); //counts messages
					printf("\nPress any key to continue\n>");
					Uin = getch();
				}
				else
				{
					printf("\nPlease enter a message first.\n");
					printf("\nPress any key to continue\n>");
					Uin = getch();
				}
				break;
			}
			case '6': //Random from file
			{
				memflag = 1;
				//Storing Messages into linked list
				for (int j = 0; j < NUMMESSAGES; j++)
				{

					flag = GetMessageFromFile(Buf, iLen);
					if (flag == 0)
					{
						create_node(Buf); //Adding message to linked list
					}
					else
					{
						printf("Error, problem reading file");
						while (true){} // stalls program
					}					
				}
				break;
			}
			case '7': //clear memory
			{
				if (memflag == 1)
				{
					clear_list('1');
					memflag = 0;
				}
				else
				{
					printf("\nPlease enter a message first.\n");
					printf("\nPress any key to continue\n>");
					Uin = getch();
				}
				break;
			}
			case '8': //hash test
			{
				flag = GetBigMessageFromFile(iBuf);
				if (flag == 0)
				{
					//puts(iBuf); //Debug
					InLen = strlen(iBuf);

					printf("\nHashing file....\n");
				}
				else
				{
					printf("Error, problem reading file");
				}
				printf("\n\nHash is %d.\n", hashU(iBuf, 29));
				getch();
				break;
			}
			case '9': //hash test
			{
				printf("\nEnter your message\n> ");
				gets(Buf);
				printf("\n\nHash is %d.\n", hashU(Buf, 29));
				getch();
				break;
			}
		}
	}
}