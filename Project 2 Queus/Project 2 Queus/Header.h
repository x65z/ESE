//Algortithms Assignment 2 "Recursion" Header
//Oct.16, 2016
//Modified assignment 1 that uses recursion to 'traverse' through linked list

#ifndef HEADER //Program wasn't compilling so added if
# define HEADER

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <ctime> 
#define NUMMESSAGES 5
#define MLENGTH 140

struct Messages {
	char buf[MLENGTH];
	int	iSend;
	int	iReceive;
	char iPriority;
	int iSeqNum;
	struct Messages *next;
};

int GetMessageFromFile(char szBuf[], int iLen);
void create_node(char message[MLENGTH]); //temp move to header
void display_list();
void traverse_list(int iNum);
void Visit();



#endif //HEADER