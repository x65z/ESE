//Algortithms Asignment 1 "Queues" Main.cpp
//Sept. 28, 2016
//Takes a random message from  an external file, queues in linked list and outputs to screen
//There are 1141 entries
using namespace std;

#include "Header.h" 

struct Messages *head = NULL;
struct Messages *curr = NULL;

void main()
{
	char Buf[140];
	int iLen = 140;
	int flag = 0;
	srand((unsigned)time(0)); //Seeds random # generator
	
	struct Messages *ptr = (struct Messages*)malloc(sizeof(struct Messages));
	
	//Storing Messages into linked list
	for (int j = 0; j < NUMMESSAGES; j++)
	{
		if (curr == ptr)
		{
			ptr = curr->next;
		}
		curr = ptr;
				
		flag = GetMessageFromFile(Buf, iLen);
		if (flag == 0)
		{
			for (int g = 0; Buf[g] != NULL; g++)
			{
				ptr->buf[g] = Buf[g];
				ptr->buf[g+1] = NULL;				
			}

			if (j == 0)
			{
				head = curr;
				struct Messages *ptr = (struct Messages*)malloc(sizeof(struct Messages));
				curr->next = ptr;		
			}
			else if (j == (NUMMESSAGES - 1))
			{
				ptr->next = NULL;
			}	
			else
			{
				struct Messages *ptr = (struct Messages*)malloc(sizeof(struct Messages));
				curr->next = ptr;

			}			
		}
		else
		{
			printf("Error, problem reading file");
			while (true){} // stalls program
		}
		

	}

	ptr = head;
	//printf("\nhead:%d\n", head);

	while (ptr != NULL)
	{
		//printf("\nptr %d\n", ptr);
		for (int i = 0; ptr->buf[i] != NULL; i++)
		{
			printf("%c", ptr->buf[i]);	// Printing Messages
		}
		printf("\n\n");
		ptr = ptr->next;
	}
	

	while (true){} // stalls program
}


