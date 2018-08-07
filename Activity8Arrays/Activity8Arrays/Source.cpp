//Activity 8 - Arrays
//Program finds the area under a curve using trapezoid approximations
#include <stdio.h>



void main()
{
	int N, Count;
	float DX;
	int Y [50];
	float Area = 0;
	char Check = 'a';
	Count = 0;

	while (Check == 'a') //Input for N
	{
		printf("Enter the number of points on the function up to a maximum of 50 points, not including the initial or '0' point.\n");
		scanf ("%d", &N);
		if (N <= 50 && N > 0)
			Check = 'b';
		else
			printf("Invalid, please reenter.\n");
	}

	Check = 'a';

	while (Check == 'a') //Input for Delta X
	{
		printf("Enter the distance between points on the function, must be positive whole.\n");
		scanf ("%f", &DX);
		if (DX >= 0)
			Check = 'b';
		else
			printf("Invalid, please reenter.\n");
	}
	while (Count <= N) // Input for all Y values, number of Y values is N
	{
		Check = 'a';
		while (Check == 'a')
		{
			printf("Enter the y-value of point %d, must be positive whole.\n", Count);
			scanf ("%d", &Y [Count]);
			if (Y [Count] >= 0)
				Check = 'b';
			else
			printf("Invalid, please reenter.\n");
		}
		Count = Count + 1;
	}

	Count = 0; // Processes Total Area based on Y values
	while (Count < N)
	{
		Area = Area + ((Y[Count] + Y [Count + 1])*(DX / 2));
		Count = Count + 1;
	}
	
	printf("\n\nApproximate area is %f.", Area); //Outputs Area

	while(true)
	{
	}
}