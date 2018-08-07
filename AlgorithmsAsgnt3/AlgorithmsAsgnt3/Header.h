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