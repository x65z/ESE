//Algortithms Assignment 2 "Recursion" Main
//Oct.16, 2016
//Modified assignment 1 that uses recursion to 'traverse' through linked list
using namespace std;
#include <string.h>
#include "Header.h" 
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

	//char str[140];


	
	//	printf("Enter your message: \n");
		//gets(str);
		//printf("You entered: %s", str);

void main()
{
	char Buf[MLENGTH];
	int iLen = MLENGTH;
	int flag = 0;
	srand((unsigned)time(0)); //Seeds random # generator
	char Uin = '0';
		
	while (Uin != 'q')
	{
		system("cls");
		printf("Press 1 to Insert a message\nPress 2 to Read messages\nPress q to quit\n> ");
		Uin = getch();

		if (Uin == '1')
		{

			printf("\nEnter your message\n> ");
			gets(Buf);
		
			create_node(Buf);
		}
	
		else if(Uin == '2') 
		{
			printf("\n");
			display_list(); //Prints messages
			printf("\nPress any key to continue.");
			Uin = getch();

		}
	}
}