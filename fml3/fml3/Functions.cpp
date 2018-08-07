//Interface Proj Interface v1  Main Zack H
//Oct. 30, 2016
//Modified assignment 2 that uses trees

#ifndef FUNC
# define FUNC
#include "Header.h" 
//#include "CommFunctions.cpp" 

struct Node *head = NULL;
struct Node *tail = NULL;
struct Node *curr = NULL;

struct book *headp = NULL;
struct book *tailp = NULL;
struct book *currp = NULL;

int GetBigMessageFromFile(char szBuf[]) //Zack
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
			if (c == 37 && Flag == 'a')
			{
				Flag = 'b';
			}
			else if (c == 37 && Flag == 'b')
			{
				Flag = 'a';
			}
			else
			{
			
				//printf("%d\n", iC);//Debug
				szBuf[iC] = c;
				
				iC++;

			}
			c = fgetc(pF);
		}
		szBuf[iC] = NULL;
		fclose(pF);
		return(0);
	}
	
	return(1);

}
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
	//printf("\nDebug: A\n");
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
	ptr->nextR = NULL;
	//printf("\nDebug: Node created, head: %d, tail %d, curr %d\n", head, tail, curr);
}

void create_phone_node(char *bSenderAddr) //phonebook
{
	//printf("\nDebug: A\n");
	struct book *ptr = (struct book*)malloc(sizeof(struct book));
	ptr->count = 0;
	if (head == NULL)
	{
		ptr->prev = NULL;
		headp = ptr;
	}
	else if (tailp != NULL)
	{
		find_ordered_tailp(bSenderAddr[0]);
		if(bSenderAddr[0] == tailp->bSenderAddr[0] && bSenderAddr[1] == tailp->bSenderAddr[1] && bSenderAddr[2] == tailp->bSenderAddr[2] && bSenderAddr[3] == tailp->bSenderAddr[3])
		{
			tailp->count = tailp->count + 1;
		}
		else if (bSenderAddr[0] < tailp->bSenderAddr[0])
		{
			tailp->nextL = ptr;			
		} 
		else
		{
			tailp->nextR = ptr;
		}
		ptr->prev = tailp;
	}

	currp = tailp = ptr;


	ptr->bSenderAddr[0] = bSenderAddr[0];
	ptr->bSenderAddr[1] = bSenderAddr[1];
	ptr->bSenderAddr[2] = bSenderAddr[2];
	ptr->bSenderAddr[3] = bSenderAddr[3];
	ptr->bSenderAddr[4] = NULL;


	ptr->nextL = NULL;
	ptr->nextR = NULL;
	//printf("\nDebug: Node created, head: %d, tail %d, curr %d\n", head, tail, curr);
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

//Sets tail phonebook
void find_ordered_tailp(char bSenderAddr)
{
	tailp = headp;
	while (tailp != NULL) //Searches alphabetically until finds a NULL
	{
		//printf("\nDEBUG:Found node, contains %c\n", tail->buf[0]); //Debug
		currp = tailp;
		if (bSenderAddr < tailp->bSenderAddr[0])
		{
			tailp = tailp->nextL;
		}
		else
		{
			tailp = tailp->nextR;
		}
	}
	tailp = currp;
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
	//printf("\nDebug: 1\n");
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

void display_listp(char flag) //Uses recursion to display phone book
{
	//printf("\nDebug: 1\n");
	struct book *dptr;
	dptr = currp;
	if (flag == '1')
	{ 
		dptr = headp;
		currp = headp;
	}
	if (dptr->nextL != NULL) //Recursive Left
	{
		currp = dptr->nextL;
		display_listp('2');
	}	

	printf("\n");
	printf("%s, %d", dptr->bSenderAddr, dptr->count);	// Printing Messages 
	
	printf("\n\n"); // Printing Messages
	printf("-----------------------------");

	if (dptr->nextR != NULL) //Recursive Right
	{
		currp = dptr->nextR;
		display_listp('2');
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

////////////////////////////////
//Compression starts

void RLEncode(char *iBuf, int InLen, char *oBuf) //Marium, heavily edited by Zack
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


//*--NEW - Universal Hash Function
int hashU(char *v, int M)
{
	int h;
	int a = 31415;
	int b = 27183;
	for (h = 0; *v != NULL; v++)
	{
		a = (a*b) % (M - 1);
		h = (h*a + *v) % M;
	}
	return(h);
}

#endif //FUNC