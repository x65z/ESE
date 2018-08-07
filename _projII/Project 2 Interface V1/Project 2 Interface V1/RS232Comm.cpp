#include "Header.h"


/*
// The client - A testing main that calls the functions below
int main() {

	char msgOut[] = "Hi there person";						// Sent message
	char msgIn[BUFSIZE];							// Received message
	initPort();										// Initialize the port
	outputToPort(msgOut, strlen(msgOut)+1);			// Send string to port - include space for '\0' termination
	Sleep(1000);	// Allow time for signal propagation on cable 
	inputFromPort(msgIn, BUFSIZE);					// Receive string from port
	 printf("\nMessage Received: %s\n\n", msgIn);	// Display message from port
	purgePort();									// Purge the port
	CloseHandle(hCom);								// Closes the handle pointing to the COM port
	system("pause");
}

*/