#ifndef COMM
# define COMM

#include "Header.h" 

char mFlag = '0';

////Comm stuff/////////////////////////////////////////////////////////////////////////////////////
//Wouldn't compile in header
#define EX_FATAL 1
#define BUFSIZE 140

// Ensure that default character set is not Unicode
// Communication variables and parameters
HANDLE hCom;										// Pointer to a COM port
int nComRate = 9600;								// Baud (Bit) rate in bits/second 
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

	printf("\n\nCOM open\n");

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

int inputFromPortBackground(LPVOID buf, DWORD szBuf) {
	int i = 0;
	DWORD NumberofBytesRead = 0;
	LPDWORD lpErrors = 0;
	LPCOMSTAT lpStat = 0;
	//while (NumberofBytesRead == 0)
	//{
		//printf("."); //Debug
		i = ReadFile(
			hCom,										// Read handle pointing to COM port
			buf,										// Buffer size
			szBuf,  									// Size of buffer - Maximum number of bytes to read
			&NumberofBytesRead,
			NULL
			);
	//}
	// Handle the timeout error
	if (i == 0) {
		printf("\nRead Error: 0x%x\n", GetLastError());
		ClearCommError(hCom, lpErrors, lpStat);		// Clears the device error flag to enable additional input and output operations. Retrieves information ofthe communications error.
	}
	else if (NumberofBytesRead > 0)
	{
		//printf("\nSuccessful reception!, There were %ld bytes read\n", NumberofBytesRead);
		//printf("\n\nMessage Received: %s\n", buf);	// Display message from port
		char mFlag = '1';
	}
	return(NumberofBytesRead);
}



// Sub functions called by above functions
/**************************************************************************************/

// Set the hCom HANDLE to point to a COM port, initialize for reading and writing, open the port and set securities
void createPortFile() {
	// Call the CreateFile() function 
	hCom = CreateFile(
		"\\\\.\\COM10",										// COM port number  --> If COM# is larger than 9 then use the following syntax--> "\\\\.\\COM10"
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
	//else {
		//printf("\nCOM is now open\n");//debug
	//}
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
///Globals
char tFlag = '0';
int iText = 0;
int iAud = 0;

void sendmenu() //sending submenu
{
	char Sin = '0';
	char msgOut[MLENGTH];
	char msgIn[MLENGTH];
	char iBuf[SLENGTH];
	char iBigBufca[SAMPLES_SEC * RECORD_TIME]; //casted
	char iBigBufco[SAMPLES_SEC * RECORD_TIME]; //compressed
	int flag = 0;

	while (Sin != 'q')
	{
		system("cls");
		printf("Coded Messaging System Alpha v.05\n--Sending Mode--\nPress 1 to send text message\nPress 2 to record audio message\nPress 3 to send audio message\nPress 4 to send random text message\nPress 5 for audio options\nPress 6 to send check file\nPress q to quit\n>");
		Sin = getch();

		switch(Sin)	
		{
			case '1' :	//send text
			{
				printf("\nPress 1 to include header\n> ");
				Sin = getch();				
				printf("\nEnter your message\n> ");
				gets(msgOut);
				if(Sin == '1')
				{
					struct Header *hptr = (struct Header*)malloc(sizeof(struct Header));
					hptr->lDataLength = strlen(msgOut); //creating header
					hptr->lSignature = 0xDEADBEEF;
					hptr->bReceiverAddr = '0xfe';
					hptr->bSenderAddr = '0xff';
					hptr->bSenderAddrb = '0xff';
					hptr->hash = hashU(msgOut, 29);
					hptr->bVersion = '1';
					hptr->bBools[0] = 0;
					hptr->bBools[1] = 0;
					hptr->bPattern[0] = 0xaa;
					hptr->bPattern[1] = 0x55;
					hptr->bPattern[2] = 0xaa;
					hptr->bPattern[3] = 0x55;

					printf("\nOutputting header\n");
					initPort();										// Initialize the port
					outputToPort(hptr, sizeof(struct Header)); //Outputting
					purgePort();									// Purge the port
					CloseHandle(hCom);
				}
				printf("\nOutputting data\n");
				initPort();										// Initialize the port
				outputToPort(msgOut, strlen(msgOut)+1); //Outputting
				purgePort();									// Purge the port
				CloseHandle(hCom);
				break;
			}
			case '2' : //record audio
			{
				InitializePlayback();			
				InitializeRecording();
				RecordBuffer(iBigBuf, lBigBufSize);
				CloseRecording();
				break;
			}
			case '3' : //send audio
			{
				printf("\n\nPress 1 to use compression\n>");
				Sin = getch();
				if (Sin == '1')
				{
					*iBigBufca = *iBigBuf;
					RLEncode(iBigBufca, sizeof(iBigBufca), iBigBufco);

					struct Header *hptr = (struct Header*)malloc(sizeof(struct Header));
					hptr->lDataLength = strlen(iBigBufco); //creating header
					hptr->lSignature = 0xDEADBEEF;
					hptr->bReceiverAddr = '0xfe';
					hptr->bSenderAddr = '0xff';
					hptr->bSenderAddrb = '0xff';
					hptr->bVersion = '1';
					hptr->bBools[0] = 1; //aud
					hptr->bBools[1] = 1; //compression
					hptr->bPattern[0] = 0xaa;
					hptr->bPattern[1] = 0x55;
					hptr->bPattern[2] = 0xaa;
					hptr->bPattern[3] = 0x55;
					printf("\nOutputting header\n");
					initPort();										// Initialize the port
					outputToPort(hptr, sizeof(struct Header)); //Outputting
					purgePort();									// Purge the port
					CloseHandle(hCom);
					
					
					initPort();										// Initialize the port
					outputToPort(iBigBufco, strlen(iBigBufco)); //Outputting
					purgePort();									// Purge the port
					CloseHandle(hCom);
				}
				else
				{
					struct Header *hptr = (struct Header*)malloc(sizeof(struct Header));
					hptr->lDataLength = lBigBufSize; //creating header
					hptr->lSignature = 0xDEADBEEF;
					hptr->bReceiverAddr = '0xfe';
					hptr->bSenderAddr = '0xff';
					hptr->bSenderAddrb = '0xff';
					hptr->bVersion = '1';
					hptr->bBools[0] = 1; //aud
					hptr->bBools[1] = 0; //no compression
					hptr->bPattern[0] = 0xaa;
					hptr->bPattern[1] = 0x55;
					hptr->bPattern[2] = 0xaa;
					hptr->bPattern[3] = 0x55;
					printf("\nOutputting header\n");
					initPort();										// Initialize the port
					outputToPort(hptr, sizeof(struct Header)); //Outputting
					purgePort();									// Purge the port
					CloseHandle(hCom);

					initPort();										// Initialize the port
					outputToPort(iBigBuf, lBigBufSize); //Outputting
					purgePort();									// Purge the port
					CloseHandle(hCom);
				}
				break;
			}
			case '4' : //send random text
			{
				initPort();										// Initialize the port
				outputToPort(iBigBuf, lBigBufSize); //Outputting
				purgePort();									// Purge the port
				CloseHandle(hCom);
				break;
			}
			case '5' : //audio options
			{
				initPort();										// Initialize the port
				outputToPort(iBigBuf, lBigBufSize); //Outputting
				purgePort();									// Purge the port
				CloseHandle(hCom);
				break;
			}
			case '6' : //send big text
			{
				printf("\nLoading file...\n");
				flag = GetBigMessageFromFile(iBuf);
				if (flag == 0)
				{
					printf("\nSending file...\n");
					initPort();										// Initialize the port
					outputToPort(iBuf, strlen(iBuf)+1); //Outputting
					purgePort();									// Purge the port
					CloseHandle(hCom);
				}
				else
				{
					printf("Error, problem reading file");
				}
				break;
			}
		}
	}
	return;
}
void recmenu() //receiving submenu
{
	int tData_Of_Receiver = 1;
	HANDLE tHandle_Of_Receiver = 0;

	tHandle_Of_Receiver = CreateThread( NULL, 0, 
           Thread_Receiver, &tData_Of_Receiver, 0, NULL); 

	if ( tHandle_Of_Receiver == NULL)
        ExitProcess(tData_Of_Receiver);

	//Array_Of_Thread_Handles[0] = tHandle_Of_Receiver;

	
	char Rin = '0';
	char msgOut[MLENGTH];
	char msgIn[MLENGTH];
	char oBuf[SLENGTH];
	char iBuf[SLENGTH];
	int dcount;
	int flag = 0;
	while (Rin != 'q')
	{
		system("cls");
		printf("Coded Messaging System Alpha v.05\n--Receiving Mode--\nYou have %d text message", iText);
			if (iText != 1)
			{
				printf("s"); //adds 's' to 'message'
			}
			printf(" and %d audio message", iAud);
			if (iAud != 1)
			{
				printf("s"); //adds 's' to 'message'
			}
			printf("\n\nPress 1 to view messages\nPress 2 for manual receive (raw data)\nPress 3 to play audio message\nPress 4 to save to file\nPress 5 to load from file\nPress 6 to compare\nPress q to quit\n> ");
			Rin = getch();
		switch(Rin)	
		{
			case '1' :	//display list
			{
				while(mFlag == '1');
				printf("\n\n");
				display_list('1'); //Prints messages
				printf("\nPress any key to continue\n>");
				getch();
				break;
			}
			case '2' : //manual
			{
				printf("\n\nClosing thread\n");
				tFlag = '1';
				WaitForSingleObject(tHandle_Of_Receiver, -1); //closing thread
				CloseHandle(tHandle_Of_Receiver);
				
				initPort();	
				inputFromPort(oBuf, SLENGTH);					// Receive string from port
				printf("\n\nMessage Received: %s\n\nPress any key to continue.", oBuf);	// Display message from port
				purgePort();									// Purge the port
				CloseHandle(hCom);
				getch();

				tHandle_Of_Receiver = CreateThread( NULL, 0,  //reopening thread
				Thread_Receiver, &tData_Of_Receiver, 0, NULL); 

				if ( tHandle_Of_Receiver == NULL)
					 ExitProcess(tData_Of_Receiver);
				break;
			}
			case '3' : //playback
			{
				printf("\nPlaying audio...");
				InitializePlayback();
				PlayBuffer(iBigBuf, lBigBufSize);
				ClosePlayback();
				break;
			}
			case '4' : //load
			{
	
				break;
			}
			case '6' : //compare
			{
				dcount = 0;
				printf("\n\nClosing thread\n");
				tFlag = '1';
				WaitForSingleObject(tHandle_Of_Receiver, -1); //closing thread
				CloseHandle(tHandle_Of_Receiver);
				
				initPort();	
				inputFromPort(oBuf, SLENGTH);					// Receive string from port
				printf("\n\nMessage Received: %s\n\nPress any key to continue.", oBuf);	// Display message from port
				purgePort();									// Purge the port
				CloseHandle(hCom);
				getch();

				tHandle_Of_Receiver = CreateThread( NULL, 0,  //reopening thread
				Thread_Receiver, &tData_Of_Receiver, 0, NULL); 

				if ( tHandle_Of_Receiver == NULL)
					 ExitProcess(tData_Of_Receiver);
				printf("\nLoading file...\n");
				
				printf("\nLoading file...\n");
				flag = GetBigMessageFromFile(iBuf);
				if (flag == 0)
				{
					for(int i=0; iBuf[i] != NULL; i++ )
					{
						if (iBuf[i]!=oBuf[i])
						dcount++;
							
					}
					printf("\nNumber of errors: %d\n", dcount);
				}
				else
				{
					printf("Error, problem reading file");
				}
				getch();
				break;
			}
		}
	}
	// Wait until all threads have terminated.
	tFlag = '1';
    WaitForSingleObject(tHandle_Of_Receiver, -1);
	CloseHandle(tHandle_Of_Receiver);
	return;
}

//-------------------------------------------
// A function for background receiver
//-------------------------------------------
DWORD WINAPI Thread_Receiver(LPVOID lpParam) 
{
	int count;
	char msgIn[MLENGTH];
	char iBigBufco[SAMPLES_SEC * RECORD_TIME];
	char iBigBufun[SAMPLES_SEC * RECORD_TIME];

	struct Header *rptr = (struct Header*)malloc(sizeof(struct Header));

	while(tFlag == '0')
	{
			initPort();	
			count = inputFromPortBackground(rptr, sizeof(struct Header));		// Receive header from port				
			purgePort();									// Purge the port
			CloseHandle(hCom);
			//printf("."); //debug
			
				if(count > 0)
				{
					if(rptr->bBools[0] == 0)
					{
						printf("\nLength: %ld\n", rptr->lDataLength);
						initPort();	
						count = inputFromPortBackground(msgIn, MLENGTH);					// Receive string from port				
						purgePort();									// Purge the port
						CloseHandle(hCom);

						if(count > 0)
						{
							printf("\nMessage Received: %s\n", msgIn);	// Display message from port
							if(hashU(msgIn, 29) == rptr->hash)
							{
								printf("\nNo errors.\n");
							}
							else
							{
								printf("\nErrors detected, original hash is %d, new hash is %d.\n",rptr->hash, hashU(msgIn, 29));
							}
							create_node(msgIn);
							char mFlag = '0';
							iText++;
						}
					}
					else
					{
						if(rptr->bBools[1] == 0) //no compression
						{
							iAud++;
							printf("\n\nReceiving uncompressed audio message...\n");
							printf("\nLength: %ld\n", rptr->lDataLength);
							initPort();	
							count = inputFromPortBackground(iBigBuf, rptr->lDataLength);					// Receive string from port				
							purgePort();									// Purge the port
							CloseHandle(hCom);
							printf("\n\nReceived audio message.\n");
						}
						else
						{
							//printf("\nDebug: bool0 = %d\n\n", rptr->bBools[0]);
							//printf("\nDebug: bool1 = %d\n\n", rptr->bBools[1]);
							iAud++;
							printf("\n\nReceiving compressed audio message...\n");
							printf("\nLength: %ld\n", rptr->lDataLength);
							initPort();	
							count = inputFromPortBackground(iBigBufco, rptr->lDataLength);					// Receive string from port				
							purgePort();									// Purge the port
							CloseHandle(hCom);
							RLDecode(iBigBufco, sizeof(iBigBufco), iBigBufun);
							*iBigBuf = *iBigBufun;
							
							printf("\n\nReceived audio message.\n");
							
						}
					}

				}
			
	}
    printf("\nThread terminated");
    return 0; 
} 


#endif //COMM