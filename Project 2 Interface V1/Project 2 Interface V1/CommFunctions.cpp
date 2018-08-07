#ifndef COMM
# define COMM

#include "Header.h" 

////Comm stuff/////////////////////////////////////////////////////////////////////////////////////
//Wouldn't compile in header
#define EX_FATAL 1
#define BUFSIZE 140

// Ensure that default character set is not Unicode
// Communication variables and parameters
HANDLE hCom;										// Pointer to a COM port
int nComRate = 115200;								// Baud (Bit) rate in bits/second 
int nComBits = 8;									// Number of bits per frame
COMMTIMEOUTS timeout;				 				// A commtimout struct variable
////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////
//Com stuff starts


////////////////////////////////////////////////////////

// Initializes the port and sets the communication parameters
void initPort() {
	createPortFile();								// Initializes hCom to point to PORT4 (port 4 is used by USB-Serial adapter on my laptop)
	purgePort();									// Purges the COM port
	SetComParms();									// Uses the DCB structure to set up the COM port
	purgePort(); 
}

// Purge any outstanding requests on the serial port (initialize)
void purgePort() {
	PurgeComm(hCom, PURGE_RXABORT | PURGE_RXCLEAR | PURGE_TXABORT | PURGE_TXCLEAR);
}

// Output message to port (COM4)
void outputToPort(LPCVOID buf, DWORD szBuf) {
	int i=0;
	DWORD NumberofBytesTransmitted;
	LPDWORD lpErrors=0;
	LPCOMSTAT lpStat=0; 

	i = WriteFile(
		hCom,										// Write handle pointing to COM port
		buf,										// Buffer size
		szBuf,										// Size of buffer
		&NumberofBytesTransmitted,					// Written number of bytes
		NULL
	);
	// Handle the timeout error
	if (i == 0) {
		printf("\nWrite Error: 0x%x\n", GetLastError());
		ClearCommError(hCom, lpErrors, lpStat);		// Clears the device error flag to enable additional input and output operations. Retrieves information ofthe communications error.	
	}
	else
		printf("\nSuccessful transmission, there were %ld bytes transmitted\n", NumberofBytesTransmitted);
}

void inputFromPort(LPVOID buf, DWORD szBuf) {
	int i = 0;
	DWORD NumberofBytesRead = 0;
	LPDWORD lpErrors = 0;
	LPCOMSTAT lpStat = 0;
	while (NumberofBytesRead == 0)
	{
		//printf("."); //Debug
		i = ReadFile(
			hCom,										// Read handle pointing to COM port
			buf,										// Buffer size
			szBuf,  									// Size of buffer - Maximum number of bytes to read
			&NumberofBytesRead,
			NULL
			);
	}
	// Handle the timeout error
	if (i == 0) {
		printf("\nRead Error: 0x%x\n", GetLastError());
		ClearCommError(hCom, lpErrors, lpStat);		// Clears the device error flag to enable additional input and output operations. Retrieves information ofthe communications error.
	}
	else
		printf("\nSuccessful reception!, There were %ld bytes read\n", NumberofBytesRead);
}



// Sub functions called by above functions
/**************************************************************************************/

// Set the hCom HANDLE to point to a COM port, initialize for reading and writing, open the port and set securities
void createPortFile() {
	// Call the CreateFile() function 
	hCom = CreateFile(
		"\\\\.\\COM11",										// COM port number  --> If COM# is larger than 9 then use the following syntax--> "\\\\.\\COM10"
		GENERIC_READ | GENERIC_WRITE,				// Open for read and write
		NULL,										// No sharing allowed
		NULL,										// No security
		OPEN_EXISTING,								// Opens the existing com port
		FILE_ATTRIBUTE_NORMAL,						// Do not set any file attributes --> Use synchronous operation
		NULL										// No template
	);

	if (hCom == INVALID_HANDLE_VALUE) {
		printf("\nFatal Error 0x%x: Unable to open\n", GetLastError());
	}
	else {
		printf("\nCOM is now open\n");
	}
}

static int SetComParms() {
	DCB dcb;										// Windows device control block
	// Clear DCB to start out clean, then get current settings
	memset(&dcb, 0, sizeof(dcb));
	dcb.DCBlength = sizeof(dcb);
	if (!GetCommState(hCom, &dcb))
		return(0);

	// Set our own parameters from Globals
	dcb.BaudRate = nComRate;						// Baud (bit) rate
	dcb.ByteSize = (BYTE)nComBits;					// Number of bits(8)
	dcb.Parity = 0;									// No parity	
	dcb.StopBits = ONESTOPBIT;						// One stop bit
	if (!SetCommState(hCom, &dcb))
		return(0);

	// Set communication timeouts (SEE COMMTIMEOUTS structure in MSDN) - want a fairly long timeout
	memset((void *)&timeout, 0, sizeof(timeout));
	timeout.ReadIntervalTimeout = 500;				// Maximum time allowed to elapse before arival of next byte in milliseconds. If the interval between the arrival of any two bytes exceeds this amount, the ReadFile operation is completed and buffered data is returned
	timeout.ReadTotalTimeoutMultiplier = 1;			// The multiplier used to calculate the total time-out period for read operations in milliseconds. For each read operation this value is multiplied by the requested number of bytes to be read
	timeout.ReadTotalTimeoutConstant = 1000;		// A constant added to the calculation of the total time-out period. This constant is added to the resulting product of the ReadTotalTimeoutMultiplier and the number of bytes (above).
	SetCommTimeouts(hCom, &timeout);
	return(1);
}

/////////////////
/////////Submenus start, had to move here so they can use COMM vars
int textmenu()
{
	int iTextt = 0;
	char Tin = '0';
	char msgOut[MLENGTH];
	char msgIn[MLENGTH];
	while (Tin != 'q')
	{
		system("cls");
		printf("Text Menu\n\nPress 1 to send a text message\nPress 2 to read text messages\nPress 3 to send random message\nPress q to exit menu");	
		Tin = getch();
		switch(Tin)	
		{
			case '1' :	//send
			{
				printf("\nEnter your message\n> ");
				gets(msgOut);											
				initPort();										// Initialize the port
				outputToPort(msgOut, strlen(msgOut)+1); //Outputting
				purgePort();									// Purge the port
				CloseHandle(hCom);
				break;
			}
			case '2' : //receive
			{
				initPort();	
				inputFromPort(msgIn, MLENGTH);					// Receive string from port
				printf("\n\nMessage Received: %s\n\nPress any key to continue.", msgIn);	// Display message from port
				purgePort();									// Purge the port
				CloseHandle(hCom);
				Tin = getch();
				break;
			}
			case '3' : //random
			{
				GetMessageFromFile(msgOut, MLENGTH);									
				initPort();										// Initialize the port
				outputToPort(msgOut, strlen(msgOut)+1); //Outputting
				purgePort();									// Purge the port
				CloseHandle(hCom);
				break;
			}
		}
	}
	return(iTextt);
}

int audmenu()
{
	int iAudd = 0;
	char Ain = '0';
	char Uin = '0';
	short *piBuf = 0;
	long lBufSize = 0;
	while (Ain != 'q')
	{
		system("cls");
		printf("Audio Menu\n\nPress 1 to record an audio message\nPress 2 to play most recent audio message\nPress 3 to send audio message\nPress 4 to receive audio messages\nPress 5 for audio options\nPress q to exit menu");	
		Ain = getch();
		switch(Ain)	
		{
			case '1' :	//record
			{
				InitializePlayback();			
				// Record the special buffer
				InitializeRecording();
				RecordBuffer(iBigBuf, lBigBufSize);
				CloseRecording();
				break;
			}
			case '2' : //play
			{
				InitializePlayback();
				PlayBuffer(iBigBuf, lBigBufSize);
				ClosePlayback();
				break;
			}
			case '3' :	//send
			{
				initPort();										// Initialize the port
				outputToPort(iBigBuf, lBigBufSize); //Outputting
				purgePort();									// Purge the port
				CloseHandle(hCom);
				break;
			}
			case '4' : //receive
			{
				initPort();	
				inputFromPort(iBigBuf, lBigBufSize);					// Receive string from port
				printf("\n\nMessage Received\n\nPress any key to continue.");	// Display message from port
				purgePort();									// Purge the port
				CloseHandle(hCom);
				Ain = getch();
				break;
			}
			case '5' : //options
			{
				printf("\n\nRecord time: %d sec\nSampling freq: %d Hz\n\n\nPress any key to continue.", RECORD_TIME, SAMPLES_SEC);	// Display message from port				
				Ain = getch();
				break;
			}
		}
	}
	return(iAudd);
}

#endif //COMM