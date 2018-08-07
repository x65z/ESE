// Data Comm Hmwrk 3 - Server Side - Zack H June 25, 2018
// Receives messages from client and stores
// Based on source code from M Galle

#include <stdlib.h>
#include "stdafx.h"
#define _WINSOCK_DEPRECATED_NO_WARNINGS 
#include <winsock2.h>
#include <WS2tcpip.h>
#include <iostream>
#include <iostream>
#include <string.h>
#include <conio.h >
#pragma comment(lib,"ws2_32.lib")  // indicates to the linker that the ws2_32.lib (Winsock library) file is needed

//prototypes
void receive_message(char sIP[200], int iPort);
void writeto_Txt(char out[200]);

int main() {
	char sIP[200] = "127.0.0.1"; //String containing IP
	char sTemp[200] = ""; //temporary string for converting user input
	int iPort = 1111; //int containing port num
	char cMenu; //Menu input
	char cFlag = '0'; //exit menu flag

	system("@cls||clear"); //clear screen
	printf("Data Communications Homework 3 - Sockets Server v2\n");


	while(cFlag == '0'){ //Main Menu Loop
		
		printf("\nIP Address: %s, Port Number: %d\n", sIP, iPort); //Status ends
		printf("\nWhat would you like to do?\n(1)Receive Message\n(2)Set IP Address\n(3)Set Port\n(q)Quit\n>"); //input prompt
		cMenu = getch();
		system("@cls||clear"); //clear screen
		switch(cMenu) {
		case '1'  : //Receive Messages
			receive_message(sIP, iPort);
			break;	
		case '2'  : //IP
			printf("Enter IP Adress:\n>");
			gets(sIP);
			break;
		case '3'  : //Port
			printf("Enter Port Number:\n>");
			gets(sTemp);
			iPort = atoi(sTemp);
			break;
		case 'q'  : //Quit
			cFlag = '1';
			break;
		default :
			printf("Invalid Input\n\n");
		}
	}
	return 0;
}

void receive_message(char sIP[200], int iPort){
	// Initialize WinSock 
	WSADATA wsaData;                        // Create a WSADATA object containing info on Windows sockets implementation
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);   // Initiate the use of WS2_32.dll 

	system("@cls||clear"); //clear screen
	printf("\nWaiting for connection...\n");

	if (iResult != 0) {
		printf("WSAStartup failed: %d\n", iResult);
		//return 1;
	}

	// Create the socket address that the listening socket will be bound to
	SOCKADDR_IN addr;  // Address the listening socket will be bound to 
	int addrlen = sizeof(addr); // length of the address 
	addr.sin_addr.s_addr = inet_addr(sIP); // Set up for local broadcast
	addr.sin_port = htons(iPort); // Port number
	addr.sin_family = AF_INET; // Defined as an IPv4 Socket

	// Create the socket to listen for new connections
	SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL); // socket to listen for new connections
	bind(sListen, (SOCKADDR*)&addr, sizeof(addr)); // Bind the address addr to the socket sListen
	listen(sListen, SOMAXCONN); // Set sListen into a listening state in which it listens for incoming connections, SOMAXCONN = socket maximum # of connections

	// Create a new socket to hold the clients connection (TCP) 
	SOCKET newConnection;  // temporary socket for holding clients new connection
	newConnection = accept(sListen, (SOCKADDR*)&addr, &addrlen); // accept new connection

	if (newConnection == 0) {
		std::cout << "\nFailed to accept the client connection. " << std::endl; 
	}
	else {
		std::cout << "\nClient connected" << std::endl;
		// Send first message from server to client
		char welcomeMsg[200] = "Thank you for connecting to the server\n";
		send(newConnection, (char*)&welcomeMsg, sizeof(welcomeMsg), NULL); 

		// Receive response from client
		char response[200];
		recv(newConnection, (char*)&response, sizeof(response), NULL); 
		std::cout << "\nMessage from client: " << response << std::endl;
		writeto_Txt(response);
	}
}

//sub for outputting to .txt file, may change to SQL in future
void writeto_Txt(char out[200]){

	FILE *f = fopen("out.txt", "w");
	if (f == NULL)
	{
		printf("Error opening file!\n");
		exit(1);
	}

	fprintf(f, "%s\n", out);
	printf("\nWrote to file.\n");

	fclose(f);
}