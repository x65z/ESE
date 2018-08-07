/*--------------------------------------------
sample06.cpp

Zack Henkusens Sept 29, 2015

Determine energy costs

Test values
Low:	250 kWh ==> $31.47
Mid:	400 kWh ==> $52.48
High:	700 kWh ==> $106.80
---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>

#define LOW 360
#define HI 680

#define LOWRATE 0.12589F
#define MIDRATE 0.17901F
#define HIRATE 0.20971F

//prototypes
void input(int *pointer_to_var, int LIMITLOW, int LIMITHI);
float processing(int kWh, int LIMITLOW, int LIMITHI);
void output(int kWh, float cost);


int main()
{
	int LIMITLOW = 0;
	int LIMITHI = 1000;
	int kWh = 0;
	float cost;

	input(&kWh, LIMITLOW, LIMITHI);	
	cost = processing(kWh, LIMITLOW, LIMITHI);
	output(kWh, cost);

	system("PAUSE");
}

void input(int *pointer_to_var, int LIMITLOW, int LIMITHI)
{
	printf ("Enter kWh used: ");
	do
	{
		scanf("%d", &*pointer_to_var);
		if ((*pointer_to_var < LIMITLOW) || (*pointer_to_var > LIMITHI))
			printf("Value is outside acceptable range of %d to %d. \
				Please reenter: ", LIMITLOW, LIMITHI);
	}
	while (*pointer_to_var < LIMITLOW || (*pointer_to_var> LIMITHI));
}

float processing(int kWh, int LIMITLOW, int LIMITHI)
{float j;
	if (kWh <= LOW)
		j = kWh * LOWRATE;
	else if (kWh <= LIMITHI)
		j = LOW * LOWRATE + (kWh - LOW) * MIDRATE;
	else
		j = LOW * LOWRATE + (HI - LOW) * MIDRATE + (kWh - HI) * HIRATE;
	return j;
}

void output(int kWh, float cost)
{
	printf("\nEnergy cost for %d kWh is $%0.2f\n", kWh, cost);
}



