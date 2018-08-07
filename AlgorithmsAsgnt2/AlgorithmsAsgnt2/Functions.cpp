//Algortithms Assignment 2 "Recursion" Functions
//Oct.16, 2016
//Modified assignment 1 that uses recursion to 'traverse' through linked list
#include "Header.h" 

struct Messages *head = NULL;
struct Messages *curr = NULL;

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
					if (iC > iLen)
					{
						iC = iLen;
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
			else
			{
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
	return(1);

}

void create_node(char message[MLENGTH])
{
	struct Messages *ptr = (struct Messages*)malloc(sizeof(struct Messages));
	if (head == NULL)
	{
		head = ptr;
	}
	if (curr != NULL)
	{
		curr->next = ptr;
	}
	curr = ptr;

	for (int g = 0; message[g] != NULL; g++)
	{
		ptr->buf[g] = message[g];
		ptr->buf[g + 1] = NULL;
	}

	ptr->next = NULL;
}

void display_list()
{
	curr = head;

	while (curr != NULL)
	{
		Visit(); // Printing Messages
		curr = curr->next;
	}

}

void traverse_list(int iNum)
{
	Messages *dptr;
	if (iNum == NUMMESSAGES)
	{
		dptr = head;
		curr = head;
	}
	else
	{
		dptr = curr->next;
		curr = dptr;
	}
	
	Visit(); // Printing Messages 

	if (iNum > 1)
	{
		traverse_list(iNum - 1); //Decides if at end of list
	}

	curr = dptr;
	Visit(); // Printing Messages Backwards
}

void Visit() //Prints Messages
{
	for (int i = 0; curr->buf[i] != NULL; i++)
	{
		printf("%c", curr->buf[i]);	// Printing Messages 
	}
	printf("\n\n");
}
