//Algorithms Assignment 6 - Graphs - Main
//Oct. 30, 2016
//Creates list of nodes and connections

#include "header.h"

void main()
{
	int node;
	int Edge;
	int nEdges;
	int v;

	Graph graphy;

	graph_init(&graphy);

	for ( node=0; node < N; ++node )
		graph_insert_vertex(&graphy);

	for ( node=0; node < N; ++node )
	{
		nEdges = (rand() % 4) + 2;

		for ( Edge=0; Edge < nEdges; )
		{
			v = (rand() % N) + 1; //Random num connections between 1 and N

			if ( v != node && graph_is_adjacent(&graphy, node, v) != 1)
			{
				graph_insert_edge(&graphy, v, node); 
				++Edge;
			}

		}

	}
	for (int i = 1; i < N; i++) //prints connections
	{
		printf("\nNode %d is connected to ", i);
		for (int y = 1; y < N; y++)
		{
			if ((graphy)[i][y] == 1)
				printf("%d ", y);
		}

	}
	printf("\nPress any key to exit.");
	getch();

}