//Algortithms Assignment 5 "Hashing" Header Zack H
//Nov. 26, 2016
//Modified assignment 3 that uses hashing

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
#define SLENGTH 300000 //Max Length of entered string, huge so can store contents of file

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

int hashU(char *v, int M);
int GetBigMessageFromFile(char szBuf[]);
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