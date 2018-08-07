/*************************
Name: Aaron K
Date: November 29th
Description: 
Makes a graph, gives it connections, and then prints them



**************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include <time.h>


void graph_init(Graph *graph)
{
	int i, x;

	*graph = (int **)malloc(N * sizeof(int *)); //mallocs the graph pointer to a pointer

	for (i = 0; i < N; i++)
		(*graph)[i] = (int *)malloc(N *sizeof(int)); //mallocs the arrays
	for (i = 0; i < N; i++)
	{
		for (x = 0; x < N; x++)
			(*graph)[i][x] = 0; //fills arrays with 0s
	}

}



void graph_destroy(Graph *g) // frees all of the mallocs
{
	int i;

	for (i = 0; i < N; i++)
		free((*g)[i]);
	free(*g);

}

void graph_insert_edge(Graph *pg, Item v1, Item v2) //insert a connection (edge)
{
	(*pg)[v1][v2] = 1;
}

int graph_is_adjacent(Graph *pg, Item v1, Item v2) // check for the connection
{
	if ((*pg)[v1][v2] == 1)
	{
		return(1);
	}
	else
	{
		return(0);
	}
}
