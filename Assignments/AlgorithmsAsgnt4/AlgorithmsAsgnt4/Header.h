#ifndef HEADER
#define HEADER

#pragma warning(disable:4996) // Disable annoying warnings

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

#define SLENGTH 300000 //Max Length of entered string, huge so can store contents of file

int GetMessageFromFile(char szBuf[]);
int GetMessageFromFileCompressed(char szBuf[]);
int WriteToFileu(char szBuf[]); //Zack
int WriteToFile(char szBuf[]);
void RLEncode( char *iBuf, int InLen, char *out);
void RLDecode(char *iBuf, int InLen, char *out);
#endif //HEADER

