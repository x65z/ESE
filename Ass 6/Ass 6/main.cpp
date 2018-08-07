/*************************
Name: Aaron K
Date: November 29th
Description:
Makes a graph, gives it connections, 
and then prints the connection spots
**************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include <time.h>




void main()
{
	int node, edge;
	int r , x;
	
	Graph pg;
	
	graph_init(&pg);

	
	for (node = 0; node < N; ++node) {
	
			r = ((rand() % 5) + 3); //picks a random number of connections to make
			for (edge = 0; edge < r;) {
				x = rand() % (N - 1); //picks where to put those connections
				if (x != node && (graph_is_adjacent(&pg, node, x)) != 1) {
						graph_insert_edge(&pg,x , node); //inserts connetions
							++edge;
					}
			}



	}
	for (size_t i = 0; i < N; i++) //prints out all of the connections
	{
		printf("\nNode %d connects to:", i);
		for (size_t y = 0; y < N; y++)
		{
			if ((pg)[i][y] == 1)
				printf("%d ", y);
		}

	}
	system("pause");
}

