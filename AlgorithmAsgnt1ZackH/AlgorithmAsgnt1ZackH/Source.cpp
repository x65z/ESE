//Algortithms Asignment 1 "Queues" Main
//Sept. 28, 2016
//Takes a random message from  an external file, queues in linked list and outputs to screen

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

string Process_File ();

void main()
{
	string Sout;

	Process_File();


	while(true){}
}

string Process_File ()
{
	string line [1200];
	int iEntries=1;

	FILE * pF;
	pF = fopen ("FortuneCookies.txt","r");
	if (pF!=NULL)
	{
		
		while (line[i] != EOF)
		{
		fscanf(pF, "%s", line);
		if (line == "%%")
		{
			printf("Entry #%d\n", iEntries);
			iEntries++;
		}
	}

		fclose (pF);
	}

	
	return("c");
}
