//Unit 9 Section A
//Zack Henkusens Dec. 15, 2015
//Program uses enum types to print the day based on entered number

#include <stdio.h>

void main()
{
	int Num = 0;
	enum days {Sunday, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday};
	
	printf("Enter a number between 1 and 7.\n");
	scanf("%d", &Num);

	printf("%s", days(Num));

	while(true);
}