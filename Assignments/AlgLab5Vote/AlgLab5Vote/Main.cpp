/* main() for VoteOn function 
 */

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#include "VoteOn.h"

struct TestStruct {
	int		i;
	float	f;
	char	c;
	short	s;
};

int main(int argc, char *argv[])
{
	// Define the variables used to test the function
	/************************************************************************************************************************************** */
	// Structures
	struct TestStruct a = { 11, 123.2, 'a', 3217 };	   // a and c are identical
	struct TestStruct b = { 11, 332.0, 'b', 3217 };
	struct TestStruct c = { 11, 123.2, 'a', 3217 };    // a and c are identical
	struct TestStruct d = { 11, 123.2, 'd', 3217 };    

	// Arrays of pointers to structures 
	struct TestStruct *List[] = { &a, &b, &c, &b, &c, &a, &b, &a };   // 3 a's, 2 c's, 3 b's. (So 5 out of 8 are same - we should print either the location of the a or the location of the c).
	struct TestStruct *List2[] = { &b, &a, &c };					  // 2 out of 3 are the same since a and c are identical
	struct TestStruct *List3[] = { &b, &a, &d };					  // all different
	struct TestStruct *List4[] = { &b, &a, &d, &c };				  // even # of elements, two are identical
	int		i;

	// Variables
	int w = 231, y = 230, z = 231;

	// Array of pointers to variables
	int *x[] = { &w, &y, &z };

	// Test the function 
	/****************************************************************************************************************************************** */
	// Test the function on arrays of pointers to structures
	i = VoteOn((void **)List, 8, sizeof(struct TestStruct));			// Notice how it is cast a 'pointer to a pointer' (using **) 
	printf("Voting on big list returned %d\n", i);						// This is because 'List' is a 'pointer' to the first element of an array of 'pointers' to structs => 'pointer to a pointer'
																		// Result: should be the location of a which is at index 0 (a and c are identical and repeated the most)
	i = VoteOn((void **)List2, 3, sizeof(struct TestStruct));
	printf("Voting on short list returned %d\n", i);					// Result:  should be index 1 since a and c are the same (a is at index 1)

	i = VoteOn((void **)List3, 3, sizeof(struct TestStruct));			
	printf("Voting on failed list returned %d\n", i);					// Result: should be -1 since none of the elements are the same

	i = VoteOn((void **)List4, 4, sizeof(struct TestStruct));
	printf("Voting on even list returned %d\n", i);						// Result: should be index 1 since a and c are the same (a is at index 1)

	i = VoteOn((void **)x, 3, sizeof(int));								// Again notice that x is cast as a 'pointer to a pointer' (using **) 
	printf("Voting on ints returned %d\n", i);							// This is because 'x' is a 'pointer' to the first element of an array of 'pointers' to int's
																		// Result: should be index 0 since w and z are the same (w is at index 0) 
	system("pause");
	return(0);
}

//Zack Henkusens Function
int	VoteOn(void *Instances[], int nInstances, int nSize)
{
	unsigned char *Table;
	int iIndex;
	int iMax = 0;
	int aMax = 0;
	int iCurr = 0;
	//printf("Instances: %d\n", nInstances);
	//printf("Instance: %d\n", Instances[0]);

	Table = (unsigned char*) calloc (nInstances*nInstances, sizeof(unsigned char));

	for (int i =0; i < nInstances; i++)
	{
		for(int j = i + 1; j < nInstances; j++)
		{
			if(memcmp(Instances[i], Instances[j], nSize) == 0)
			{
				//Matches
				iIndex = (i*nInstances) + j;
				Table[iIndex] = 1;
			}
		}
	}

	for(int i = 0; i < nInstances; i++)
	{
		iIndex = (i * nInstances);
		iCurr = 1;
		for(int j = 0; j < nInstances; j++)
		{
			iIndex = (i*nInstances) + j;
			if (Table[iIndex] == 1)
			{
				iCurr++;
			}
		}
		if(iCurr > iMax)
		{
			iMax = iCurr;
			aMax = i;
		}
	}
	
	if (iMax >= (nInstances + 1) / 2)
	{
		return(aMax);
	}
	else
	{
		return(-1);
	}
}