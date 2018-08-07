//Final Program
// Dec. 15, 2015 Zack Henkusens
//Program Opens a binary file containing data about voltage readings and displays the data in a table

#include <stdio.h>

//Prototypes
void outReadings(int NumReadings, int *Time, float *Reading);

void main()
{
	int NumReadings = 0;
	int *Time;
	float *Reading;

	FILE *MyFile; //I tried to move this whole block into its own function, but I also wanted to dynamically allocate memory and doing those two things at once seems nearly impossible
	MyFile=fopen("vdata.dat","rb");
	if (!MyFile)
		{
			printf("\n\nCan't open file.");
		}
	else
		{
			fread(&NumReadings, 4, 1, MyFile);

			Time = new int [NumReadings]; //Dynamically allocates memory depending on size of file
			Reading = new float [NumReadings];

			for(int i = 0; i < NumReadings; i++)
			{
				Time[i] = 0;
				Reading[i] = 0;
				fseek(MyFile, 0, SEEK_SET);
				fseek(MyFile, 4 + i*8, SEEK_CUR);
				fread(&Time[i], 4, 1, MyFile);
				fread(&Reading[i], 4, 1, MyFile);

			}

		}
	fclose(MyFile);
	
	outReadings(NumReadings, Time, Reading); //Formats and outputs data

	//Wait til the cows come home
	while(true);


}

void outReadings(int NumReadings, int *Time, float *Reading)
{
	printf("%d entries\n", NumReadings);
	printf("\n\n   --Time--   --Reading--\n\n");

	for(int i = 0; i < NumReadings; i++)
	{
		printf("\n   %.2d:%.2d:%.2d       %.2f", Time[i] / 60 / 60, (Time[i] / 60) % 60, Time[i] % 60, Reading[i]);
	}
}
