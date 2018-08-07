//Algortithms Assignment 3 "Trees" Header Zack H
//Oct. 30, 2016
//Modified assignment 2 that uses trees

#ifndef HEADER
# define HEADER

#pragma warning(disable:4996) // Disable annoying warnings

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <ctime> 
#define NUMMESSAGES 10
#define MLENGTH 140

struct Node {
	char buf[MLENGTH];
	int	iSend;
	int	iReceive;
	char iPriority;
	int iSeqNum;
	struct Node *nextL;
	struct Node *nextR;
	struct Node *prev;
};

int GetMessageFromFile(char szBuf[], int iLen);
void create_node(char message[MLENGTH]);
void find_ordered_tail(char fbuf);
void search(char fbuf);
int height_list(char flag);
void display_list(char flag);
int count_list(char flag); //counts messages
void clear_list(char flag);
void Visit(struct Node *vptr);



#endif //HEADER


--------------------------------------------------------------------------------------------------

//Algortithms Assignment 3 "Trees"  Main Zack H
//Oct. 30, 2016
//Modified assignment 2 that uses trees
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
	int flag = 0;
	int memflag = 0;//Is there anything stored in memory?
	srand((unsigned)time(0)); //Seeds random # generator
	char Uin = '0';

	while (Uin != 'q')
	{
		system("cls");
		printf("Press 1 to insert a message\nPress 2 to read messages\nPress 3 to search messages\nPress 4 to count messages\nPress 5 to determine max tree height\nPress 6 to add 10 random messages\nPress 7 to clear messages\nPress q to quit\n> ");
		Uin = getch();

		if (Uin == '1')
		{
			memflag = 1;
			printf("\nEnter your message\n> ");
			gets(Buf);

			create_node(Buf);
		}

		else if (Uin == '2')
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

		}
		else if (Uin == '3')
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
		}
		else if (Uin == '4')
		{
			if (memflag == 1)
			{
				printf("\nThere are %d messages.",count_list('1')); //counts messages
				printf("\nPress any key to continue\n>");
				Uin = getch();
			}
			else
			{
				printf("\nPlease enter a message first.\n");
				printf("\nPress any key to continue\n>");
				Uin = getch();
			}
		}
		else if (Uin == '5')
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
		}
		else if (Uin == '6')
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
		}
		else if (Uin == '7')
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
		}
	}
}



--------------------------------------------------------------------------------------------------

//Algortithms Assignment 3 "Trees" Functions Zack H
//Oct. 30, 2016
//Modified assignment 2 that uses trees
#include "Header.h" 

struct Node *head = NULL;
struct Node *tail = NULL;
struct Node *curr = NULL;

int GetMessageFromFile(char szBuf[], int iLen)
{
	char Flag = 'a'; //Var is used to detect double %
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
			if (c == 37 && Flag == 'a')
			{
				Flag = 'b';
				if (iEntries - 1 == iLook)
				{
					if (iC > iLen - 1)
					{
						iC = iLen - 1;
					}
					szBuf[iC] = NULL;
				}
				iEntries++;
				iC = 0;
			}
			else if (c == 37 && Flag == 'b')
			{
				Flag = 'a';
			}
			else if ((c != '\n' || iC != 0) && c != '"') //Will not save newline or opening quotes
			{
				if (iC < (iLen-1) && (iEntries - 1) == iLook)
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
	return(1);

}

void create_node(char message[MLENGTH])
{
	struct Node *ptr = (struct Node*)malloc(sizeof(struct Node));
	if (head == NULL)
	{
		ptr->prev = NULL;
		head = ptr;
	}
	else if (tail != NULL)
	{
		find_ordered_tail(message[0]);
		if (message[0] < tail->buf[0])
		{
			tail->nextL = ptr;
		}
		else
		{
			tail->nextR = ptr;
		}
		ptr->prev = tail;
	}

	curr = tail = ptr;

	for (int g = 0; message[g] != NULL; g++)
	{
		ptr->buf[g] = message[g];
		ptr->buf[g + 1] = NULL;
	}

	ptr->nextL = NULL;
	ptr->nextL = NULL;
	ptr->nextR = NULL;
}

//Sets tail
void find_ordered_tail(char fbuf)
{
	tail = head;
	while (tail != NULL) //Searches alphabetically until finds a NULL
	{
		//printf("\nDEBUG:Found node, contains %c\n", tail->buf[0]); //Debug
		curr = tail;
		if (fbuf < tail->buf[0])
		{
			tail = tail->nextL;
		}
		else
		{
			tail = tail->nextR;
		}
	}
	tail = curr;
}

void search(char fbuf)
{
	tail = head;
	while (tail != NULL) //Searches alphabetically until finds a NULL
	{
		//printf("\nDEBUG:Found node, contains %c\n", tail->buf[0]); //Debug
		curr = tail;
		if (fbuf == tail->buf[0])
		{
			printf("\n\nFound:\n");
			Visit(tail);
			printf("-----------------------------");
		}
		if (fbuf < tail->buf[0])
		{
			tail = tail->nextL;
		}
		else
		{
			tail = tail->nextR;
		}
	}
	tail = curr;
}

void display_list(char flag) //Uses recursion to display all nodes alphabetically
{
	struct Node *dptr;
	dptr = curr;
	if (flag == '1')
	{ 
		dptr = head;
		curr = head;
	}
	if (dptr->nextL != NULL) //Recursive Left
	{
		curr = dptr->nextL;
		display_list('2');
	}	

	printf("\n");
	Visit(dptr); // Printing Messages
	printf("-----------------------------");

	if (dptr->nextR != NULL) //Recursive Right
	{
		curr = dptr->nextR;
		display_list('2');
	}

}

int count_list(char flag) //counts messages
{
	int i = 1;
	struct Node *cptr;
	cptr = curr;
	if (flag == '1')
	{
		cptr = head;
		curr = head;
	}
	if (cptr->nextL != NULL) //Recursive Left
	{
		curr = cptr->nextL;
		i = i + count_list('2');
	}

	if (cptr->nextR != NULL) //Recursive Right
	{
		curr = cptr->nextR;
		i = i + count_list('2');
	}
	return(i);
}

int height_list(char flag) //finds heigt of head node
{
	int iL = 1;
	int iR = 1;
	struct Node *hptr;
	hptr = curr;
	if (flag == '1')
	{
		hptr = head;
		curr = head;
	}
	if (hptr->nextL != NULL) //Recursive Left
	{
		curr = hptr->nextL;
		iL = iL + height_list('2');
	}

	if (hptr->nextR != NULL) //Recursive Right
	{
		curr = hptr->nextR;
		iR = iR + height_list('2');
	}
	if (iL > iR)
	{
		return(iL);
	}
	else
	{
		return(iR);
	}
}

void display_listL() //OLD -- only displays left side of tree
{
	curr = head;
	int i = 1;
	while (curr != NULL)
	{
		printf("%d.\n\n", i);
		i++;
		Visit(curr); // Printing Messages
		curr = curr->nextL;
	}

}

void clear_list(char flag) //frees memory, clears tree
{
	struct Node *cptr;
	cptr = curr;
	if (flag == '1')
	{
		cptr = head;
		curr = head;
	}
	if (cptr->nextL != NULL) //Recursive Left
	{
		curr = cptr->nextL;
		clear_list('2');
	}


	if (cptr->nextR != NULL) //Recursive Right
	{
		curr = cptr->nextR;
		clear_list('2');
	}
	free(cptr); // freeing memory
	if (flag == '1')
	{
		head = tail = curr = NULL;
	}
}


void Visit(struct Node *vptr) //Prints Messages
{
	for (int i = 0; vptr->buf[i] != NULL; i++)
	{
		printf("%c", vptr->buf[i]);	// Printing Messages 
	}
	printf("\n\n");
}
