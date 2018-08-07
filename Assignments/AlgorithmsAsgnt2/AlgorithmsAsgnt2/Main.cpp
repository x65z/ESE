//Algortithms Assignment 2 "Recursion" Main
//Oct.16, 2016
//Modified assignment 1 that uses recursion to 'traverse' through linked list
using namespace std;

#include "Header.h" 

void main()
{
	char Buf[MLENGTH];
	int iLen = MLENGTH;
	int flag = 0;
	srand((unsigned)time(0)); //Seeds random # generator

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

	//display_list(); //Prints messages only once
	traverse_list(NUMMESSAGES); //Function prints messages in forward and reverse

	while (true){} // stalls program
}


