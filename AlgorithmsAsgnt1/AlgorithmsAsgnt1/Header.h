//Algortithms Asignment 1 "Queues" Header.h
//Sept. 28, 2016
//Takes a random message from  an external file, queues in linked list and outputs to screen
//There are 1141 entries

#ifndef HEADER //Program wasn't compilling so added if
# define HEADER

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <ctime> 
#define NUMMESSAGES 5

struct Messages {
	char buf[140];
	int	iSend;
	int	iReceive;
	char iPriority;
	int iSeqNum;
	struct Messages *next;
};

int GetMessageFromFile(char szBuf[], int iLen);

#endif //HEADER