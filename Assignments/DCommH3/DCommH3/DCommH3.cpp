// Data Comm Hmwrk 3 - Client Side - Zack H June 25, 2018
// takes user input and sends to server
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
void send_message(char sMessage[200], char sIP[200], int iPort);

int main(){
	char asUM [8][200]; //array of strings to be sent
	char sUM[200] = ""; //compiled user message
	char sIP[200] = "127.0.0.1"; //String containing IP
	char sTemp[200] = ""; //temporary string for converting user input
	int iPort = 1111; //int containing port num
	char cMenu; //Menu input
	char cFlag = '0'; //exit menu flag
	char cMessageFlag = '0'; //message ready flag 

	system("@cls||clear"); //clear screen
	printf("Data Communications Homework 3 - Sockets Client v2\n");


	while(cFlag == '0'){ //Main Menu Loop
		
		if(cMessageFlag == '0'){
			printf("\nMessage not ready.\n");
		}else{
			printf("\nMessage ready.\n");
		}
		printf("\nIP Address: %s, Port Number: %d\n", sIP, iPort); //Status ends
		printf("\nWhat would you like to do?\n(1)Enter Message\n(2)Set IP Address\n(3)Set Port\n(4)Send Message\n(5)Clear Message\n(q)Quit\n>"); //input prompt
		cMenu = getch();
		system("@cls||clear"); //clear screen
		switch(cMenu) {
		case '1'  : //Enter Message
			printf("Enter Name:\n>");
			gets(asUM[0]);
			printf("Enter ID:\n>");
			gets(asUM[1]);
			printf("Enter Street Number:\n>");
			gets(asUM[2]);
			printf("Enter Street Name:\n>");
			gets(asUM[3]);
			printf("Enter City:\n>");
			gets(asUM[4]);
			printf("Enter Postal Code:\n>");
			gets(asUM[5]);
			printf("Enter Province:\n>");
			gets(asUM[6]);
			printf("Enter Country:\n>");
			gets(asUM[7]);
			cMessageFlag = '1';
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
		case '4'  : //Send
			if (cMessageFlag == '0'){
				printf("\nEnter Message first.\n");
			}else{
				strcpy(sUM, "\nName:");
				strcat(sUM, asUM[0]);
				strcat(sUM, "\nID:");
				strcat(sUM, asUM[1]);
				strcat(sUM, "\nStreet Number:");
				strcat(sUM, asUM[2]);
				strcat(sUM, "\nStreet Name:");
				strcat(sUM, asUM[3]);
				strcat(sUM, "\nCity:");
				strcat(sUM, asUM[4]);
				strcat(sUM, "\nPostal Code:");
				strcat(sUM, asUM[5]);
				strcat(sUM, "\nProvince:");
				strcat(sUM, asUM[6]);
				strcat(sUM, "\nCountry:");
				strcat(sUM, asUM[7]);
				//puts(sUM); //debug
				send_message(sUM, sIP, iPort);
			}
			break;
		case '5'  : //Clear
			for(int i=0; i < 8; i++){
				strcpy(asUM[i], "");
			}
			cMessageFlag = '0';
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

//Function for sending message through Socket, adapted from M Galle's example
void send_message(char sMessage[200], char sIP[200], int iPort){
	// Initialize WinSock 
	WSADATA wsaData;                        // Create a WSADATA object containing info on Windows sockets implementation
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);   // Initiate the use of WS2_32.dll 
	if (iResult != 0) {
		printf("WSAStartup failed: %d\n", iResult);
		//return 1;
	}
	// Create address to bind to the Connection Socket
	SOCKADDR_IN addr;  // Address to bind to Connection Socket
	int addrlen = sizeof(addr); // length of the address 
	addr.sin_addr.s_addr = inet_addr(sIP); // Address = localhost (this pc - for this example)
	addr.sin_port = htons(iPort); // Port number = 1111 in this example
	addr.sin_family = AF_INET; // Defined as an IPv4 Socket

	// Create the connection socket
	SOCKET Connection = socket(AF_INET, SOCK_STREAM, NULL); // sets the connection socket
	if (connect(Connection, (SOCKADDR*)&addr, addrlen) != 0) {    // cannot connect to server
		std::cout << "Server failed to accept the client connection.\n " << std::endl;
	}
	else {
		std::cout << "Connected to server\n" << std::endl;

		// Receive welcome message from server
		char welcomeMsg[200]; 
		recv(Connection, (char*)&welcomeMsg, sizeof(welcomeMsg), NULL); // Receive message from Server
		std::cout << "Message from server:\n " << welcomeMsg << std::endl;
		
		// Send response to server
		//char response[200] = "Thank you for accepting my connection"; 
		char response[200];
		strcpy(response, sMessage);
		send(Connection, (char*)&response, sizeof(response), NULL); //old
		//puts(sMessage); //debug

		//send(Connection, (char*)&sMessage, sizeof(sMessage), NULL); 
	}
	//system("pause");
	//return(0);
}
