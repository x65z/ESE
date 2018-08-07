//Midterm Section 2 Program - Colossus Airlines Seat Reservation Manager V1

#include <stdio.h>
#include <conio.h> //so I can _getche
#include <string.h> //so I can use strcpy
#include <stdlib.h>  //so I can clear the screen

#define NAMELENGTH 20 //Max char length of first and last names

	struct Seat_Data {
		char Reserved;
		char FirstN [NAMELENGTH];
		char LastN [NAMELENGTH];
	} Seat1, Seat2, Seat3, Seat4, Seat5, Seat6, Seat7, Seat8, Seat9, Seat10, Seat11, Seat12;


//Prototypes
void numempty (Seat_Data &Seat1,Seat_Data &Seat2, Seat_Data &Seat3, Seat_Data &Seat4, Seat_Data &Seat5, Seat_Data &Seat6, Seat_Data &Seat7, Seat_Data &Seat8, Seat_Data &Seat9, Seat_Data &Seat10, Seat_Data &Seat11, Seat_Data &Seat12);
void showempty (Seat_Data &Seat1,Seat_Data &Seat2, Seat_Data &Seat3, Seat_Data &Seat4, Seat_Data &Seat5, Seat_Data &Seat6, Seat_Data &Seat7, Seat_Data &Seat8, Seat_Data &Seat9, Seat_Data &Seat10, Seat_Data &Seat11, Seat_Data &Seat12);
void listnames (Seat_Data &Seat1,Seat_Data &Seat2, Seat_Data &Seat3, Seat_Data &Seat4, Seat_Data &Seat5, Seat_Data &Seat6, Seat_Data &Seat7, Seat_Data &Seat8, Seat_Data &Seat9, Seat_Data &Seat10, Seat_Data &Seat11, Seat_Data &Seat12);
void assignseat (Seat_Data &Seat1,Seat_Data &Seat2, Seat_Data &Seat3, Seat_Data &Seat4, Seat_Data &Seat5, Seat_Data &Seat6, Seat_Data &Seat7, Seat_Data &Seat8, Seat_Data &Seat9, Seat_Data &Seat10, Seat_Data &Seat11, Seat_Data &Seat12);
void clearseat (Seat_Data &Seat1,Seat_Data &Seat2, Seat_Data &Seat3, Seat_Data &Seat4, Seat_Data &Seat5, Seat_Data &Seat6, Seat_Data &Seat7, Seat_Data &Seat8, Seat_Data &Seat9, Seat_Data &Seat10, Seat_Data &Seat11, Seat_Data &Seat12);

void main()
{
	//Seat1
	Seat1.Reserved = 'n';
	strcpy( Seat1.FirstN, "N/A");
	strcpy( Seat1.LastN, "N/A");

	//Seat2
	Seat2.Reserved = 'n';
	strcpy( Seat2.FirstN, "N/A");
	strcpy( Seat2.LastN, "N/A");

	//Seat3
	Seat3.Reserved = 'n';
	strcpy( Seat3.FirstN, "N/A");
	strcpy( Seat3.LastN, "N/A");

	//Seat4
	Seat4.Reserved = 'n';
	strcpy( Seat4.FirstN, "N/A");
	strcpy( Seat4.LastN, "N/A");

	//Seat5
	Seat5.Reserved = 'n';
	strcpy( Seat5.FirstN, "N/A");
	strcpy( Seat5.LastN, "N/A");

	//Seat6
	Seat6.Reserved = 'n';
	strcpy( Seat6.FirstN, "N/A");
	strcpy( Seat6.LastN, "N/A");

	//Seat7
	Seat7.Reserved = 'n';
	strcpy( Seat7.FirstN, "N/A");
	strcpy( Seat7.LastN, "N/A");

	//Seat8
	Seat8.Reserved = 'n';
	strcpy( Seat8.FirstN, "N/A");
	strcpy( Seat8.LastN, "N/A");

	//Seat9
	Seat9.Reserved = 'n';
	strcpy( Seat9.FirstN, "N/A");
	strcpy( Seat9.LastN, "N/A");

	//Seat10
	Seat10.Reserved = 'n';
	strcpy( Seat10.FirstN, "N/A");
	strcpy( Seat10.LastN, "N/A");

	//Seat11
	Seat11.Reserved = 'n';
	strcpy( Seat11.FirstN, "N/A");
	strcpy( Seat11.LastN, "N/A");

	//Seat12
	Seat12.Reserved = 'n';
	strcpy( Seat12.FirstN, "N/A");
	strcpy( Seat12.LastN, "N/A");

	char UIn;
	char ExitFlag = 'a';

	while (ExitFlag == 'a')
	{
		printf("Colossus Airlines Seat Reservation Manager V1\n\nEnter a character to use the listed function.\n\na. Show number of empty seats\nb. Show list of empty seats\nc. Show list of seat holders\nd. Assign a customer to a seat\ne. Delete a seat assignment\nf. Quit\n\n>");
		UIn = _getche();

		if (UIn == 'a')
			numempty(Seat1, Seat2, Seat3, Seat4, Seat5, Seat6, Seat7, Seat8, Seat9, Seat10, Seat11, Seat12);
		else if (UIn == 'b')
			showempty(Seat1, Seat2, Seat3, Seat4, Seat5, Seat6, Seat7, Seat8, Seat9, Seat10, Seat11, Seat12);
		else if (UIn == 'c')
			listnames(Seat1, Seat2, Seat3, Seat4, Seat5, Seat6, Seat7, Seat8, Seat9, Seat10, Seat11, Seat12);
		else if (UIn == 'd')
			assignseat(Seat1, Seat2, Seat3, Seat4, Seat5, Seat6, Seat7, Seat8, Seat9, Seat10, Seat11, Seat12);
		else if (UIn == 'e')
			clearseat(Seat1, Seat2, Seat3, Seat4, Seat5, Seat6, Seat7, Seat8, Seat9, Seat10, Seat11, Seat12);
		else if (UIn == 'f')
			ExitFlag = 'b';
		
		else
			printf("\nInvalid, reenter.");

		printf("\nPress any key to continue.\n");
		_getch();

		system("CLS");
	}
}

void numempty (Seat_Data &Seat1,Seat_Data &Seat2, Seat_Data &Seat3, Seat_Data &Seat4, Seat_Data &Seat5, Seat_Data &Seat6, Seat_Data &Seat7, Seat_Data &Seat8, Seat_Data &Seat9, Seat_Data &Seat10, Seat_Data &Seat11, Seat_Data &Seat12)
{
	int Count = 0;
	
	if (Seat1.Reserved == 'n')
		Count = Count + 1;

	if (Seat2.Reserved == 'n')
		Count = Count + 1;
	
	if (Seat3.Reserved == 'n')
		Count = Count + 1;
	
	if (Seat4.Reserved == 'n')
		Count = Count + 1;
	
	if (Seat5.Reserved == 'n')
		Count = Count + 1;
	
	if (Seat6.Reserved == 'n')
		Count = Count + 1;
	
	if (Seat7.Reserved == 'n')
		Count = Count + 1;
	
	if (Seat8.Reserved == 'n')
		Count = Count + 1;
	
	if (Seat9.Reserved == 'n')
		Count = Count + 1;
	
	if (Seat10.Reserved == 'n')
		Count = Count + 1;
	
	if (Seat11.Reserved == 'n')
		Count = Count + 1;
	
	if (Seat12.Reserved == 'n')
		Count = Count + 1;

printf("\n\nThere are %d empty seat(s).\n", Count);
}

void showempty (Seat_Data &Seat1,Seat_Data &Seat2, Seat_Data &Seat3, Seat_Data &Seat4, Seat_Data &Seat5, Seat_Data &Seat6, Seat_Data &Seat7, Seat_Data &Seat8, Seat_Data &Seat9, Seat_Data &Seat10, Seat_Data &Seat11, Seat_Data &Seat12)
{
	printf("\n\nIs seat occupied? 'y' is yes, 'n' is no.\n\nSeat 1  %c Seat 2  %c\nSeat 3  %c Seat 4  %c\nSeat 5  %c Seat 6  %c\nSeat 7  %c Seat 8  %c\nSeat 9  %c Seat 10 %c\nSeat 11 %c Seat 12 %c\n", Seat1.Reserved, Seat2.Reserved, Seat3.Reserved, Seat4.Reserved, Seat5.Reserved, Seat6.Reserved, Seat7.Reserved, Seat8.Reserved, Seat9.Reserved, Seat10.Reserved, Seat11.Reserved, Seat12.Reserved);

}

void listnames (Seat_Data &Seat1,Seat_Data &Seat2, Seat_Data &Seat3, Seat_Data &Seat4, Seat_Data &Seat5, Seat_Data &Seat6, Seat_Data &Seat7, Seat_Data &Seat8, Seat_Data &Seat9, Seat_Data &Seat10, Seat_Data &Seat11, Seat_Data &Seat12)
{
	printf("\n\nSeat 1 %s %s  Seat 2 %s %s\nSeat 3 %s %s Seat 4 %s %s\nSeat 5 %s %s  Seat 6 %s %s\nSeat 7 %s %s  Seat 8 %s %s\nSeat 9 %s %s  Seat 10 %s %s\nSeat 11 %s %s Seat 12 %s %s\n", Seat1.FirstN, Seat1.LastN, Seat2.FirstN, Seat2.LastN, Seat3.FirstN, Seat3.LastN, Seat4.FirstN, Seat4.LastN, Seat5.FirstN, Seat5.LastN, Seat6.FirstN, Seat6.LastN, Seat7.FirstN, Seat7.LastN, Seat8.FirstN, Seat8.LastN, Seat9.FirstN, Seat9.LastN, Seat10.FirstN, Seat10.LastN, Seat11.FirstN, Seat11.LastN, Seat12.FirstN, Seat12.LastN);
}

void assignseat (Seat_Data &Seat1,Seat_Data &Seat2, Seat_Data &Seat3, Seat_Data &Seat4, Seat_Data &Seat5, Seat_Data &Seat6, Seat_Data &Seat7, Seat_Data &Seat8, Seat_Data &Seat9, Seat_Data &Seat10, Seat_Data &Seat11, Seat_Data &Seat12)
{
	int UCh = 0;
	char Buffer [NAMELENGTH] = {NULL};
	char ExitLFlag = 'a';

	while (ExitLFlag == 'a')
	{
		printf("\n\nWhich seat between 1 and 12 would you like to assign the customer to?\n");
		scanf("%i", &UCh);

		if (UCh < 1 || UCh > 12)
			printf("\nInvalid, Reenter.\n");
		else
			ExitLFlag = 'b';

		system("CLS");
	}

	printf("Enter first name.\n");
	gets(Buffer); //Needs to buffer twice so input doesn't spill over, works seamlessly while actually executing
	gets(Buffer);

	if (UCh == 1)
		strcpy( Seat1.FirstN, Buffer);
	else if (UCh == 2)
		strcpy( Seat2.FirstN, Buffer);
	else if (UCh == 3)
		strcpy( Seat3.FirstN, Buffer);
	else if (UCh == 4)
		strcpy( Seat4.FirstN, Buffer);
	else if (UCh == 5)
		strcpy( Seat5.FirstN, Buffer);
	else if (UCh == 6)
		strcpy( Seat6.FirstN, Buffer);
	else if (UCh == 7)
		strcpy( Seat7.FirstN, Buffer);
	else if (UCh == 8)
		strcpy( Seat8.FirstN, Buffer);
	else if (UCh == 9)
		strcpy( Seat9.FirstN, Buffer);
	else if (UCh == 10)
		strcpy( Seat10.FirstN, Buffer);
	else if (UCh == 11)
		strcpy( Seat11.FirstN, Buffer);
	else if (UCh == 12)
		strcpy( Seat12.FirstN, Buffer);

	printf("\nEnter last name.\n");
	gets(Buffer);

	if (UCh == 1)
		{
			strcpy( Seat1.LastN, Buffer);
			Seat1.Reserved = 'y';
		}
	else if (UCh == 2)
		{
			strcpy( Seat2.LastN, Buffer);
			Seat2.Reserved = 'y';
		}
	else if (UCh == 3)
		{
			strcpy( Seat3.LastN, Buffer);
			Seat3.Reserved = 'y';
		}
	else if (UCh == 4)
		{
			strcpy( Seat4.LastN, Buffer);
			Seat4.Reserved = 'y';
		}
	else if (UCh == 5)
		{
			strcpy( Seat5.LastN, Buffer);
			Seat5.Reserved = 'y';
		}
	else if (UCh == 6)
		{
			strcpy( Seat6.LastN, Buffer);
			Seat6.Reserved = 'y';
		}
	else if (UCh == 7)
		{
			strcpy( Seat7.LastN, Buffer);
			Seat7.Reserved = 'y';
		}
	else if (UCh == 8)
		{
			strcpy( Seat8.LastN, Buffer);
			Seat8.Reserved = 'y';
		}
	else if (UCh == 9)
		{
			strcpy( Seat9.LastN, Buffer);
			Seat9.Reserved = 'y';
		}
	else if (UCh == 10)
		{
			strcpy( Seat10.LastN, Buffer);
			Seat10.Reserved = 'y';
		}
	else if (UCh == 11)
		{
			strcpy( Seat11.LastN, Buffer);
			Seat11.Reserved = 'y';
		}
	else if (UCh == 12)
		{
			strcpy( Seat12.LastN, Buffer);
			Seat12.Reserved = 'y';
		}
}

void clearseat (Seat_Data &Seat1,Seat_Data &Seat2, Seat_Data &Seat3, Seat_Data &Seat4, Seat_Data &Seat5, Seat_Data &Seat6, Seat_Data &Seat7, Seat_Data &Seat8, Seat_Data &Seat9, Seat_Data &Seat10, Seat_Data &Seat11, Seat_Data &Seat12)
	{
	int UCh = 0;
	char ExitLFlag = 'a';

	while (ExitLFlag == 'a')
	{
		printf("\n\nWhich seat between 1 and 12 would you like to clear?\n");
		scanf("%i", &UCh);

		if (UCh < 1 || UCh > 12)
			printf("\nInvalid, Reenter.\n");
		else
			ExitLFlag = 'b';

		system("CLS");
	}

	if (UCh == 1)
	{
		Seat1.Reserved = 'n';
		strcpy(Seat1.FirstN, "N/A");
		strcpy(Seat1.LastN, "N/A");
	}
	else if (UCh == 2)
	{
		Seat2.Reserved = 'n';
		strcpy(Seat2.FirstN, "N/A");
		strcpy(Seat2.LastN, "N/A");
	}
	else if (UCh == 3)
	{
		Seat3.Reserved = 'n';
		strcpy(Seat3.FirstN, "N/A");
		strcpy(Seat3.LastN, "N/A");
	}
	else if (UCh == 4)
	{
		Seat4.Reserved = 'n';
		strcpy(Seat4.FirstN, "N/A");
		strcpy(Seat4.LastN, "N/A");
	}
	else if (UCh == 5)
	{
		Seat5.Reserved = 'n';
		strcpy(Seat5.FirstN, "N/A");
		strcpy(Seat5.LastN, "N/A");
	}
	else if (UCh == 6)
	{
		Seat3.Reserved = 'n';
		strcpy(Seat6.FirstN, "N/A");
		strcpy(Seat6.LastN, "N/A");
	}
	else if (UCh == 7)
	{
		Seat7.Reserved = 'n';
		strcpy(Seat7.FirstN, "N/A");
		strcpy(Seat7.LastN, "N/A");
	}
	else if (UCh == 8)
	{
		Seat8.Reserved = 'n';
		strcpy(Seat8.FirstN, "N/A");
		strcpy(Seat8.LastN, "N/A");
	}
	else if (UCh == 9)
	{
		Seat9.Reserved = 'n';
		strcpy(Seat9.FirstN, "N/A");
		strcpy(Seat9.LastN, "N/A");
	}
	else if (UCh == 10)
	{
		Seat10.Reserved = 'n';
		strcpy(Seat10.FirstN, "N/A");
		strcpy(Seat10.LastN, "N/A");
	}
	else if (UCh == 11)
	{
		Seat1.Reserved = 'n';
		strcpy(Seat11.FirstN, "N/A");
		strcpy(Seat11.LastN, "N/A");

	}
	else if (UCh == 12)
	{
		Seat12.Reserved = 'n';
		strcpy(Seat12.FirstN, "N/A");
		strcpy(Seat12.LastN, "N/A");
	}
}