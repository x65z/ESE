//Algorithms Assignment 6 - Graphs - Functions
//Oct. 30, 2016
//Creates list of nodes and connections

#include "header.h"

void graph_init(Graph *graph) // initialize graph
{
	int i, x;
	*graph = (int **)malloc(N * sizeof(int *)); //Making a pointer

	for (i = 0; i < N; i++)
		(*graph)[i] = (int *)malloc(N *sizeof(int)); //creating arrays
	for (i = 0; i < N; i++)
	{
		for (x = 0; x < N; x++)
			(*graph)[i][x] = 0; //clearing
	}
}
void graph_insert_vertex(Graph *graph)
{
	int r;
	int edge;
	int x;
	int n = 0;
	r = ((rand() % 5) + 3); //Random num connections between 3 and 8
			for (edge = 0; edge < r;) {
				x = rand() % (N - 1);
				if (x != n && (graph_is_adjacent(graph, n, x)) != 1) {
						graph_insert_edge(graph,x , n); //inserts connetions into graph
							++edge;
					}
			}

}

void graph_insert_edge(Graph *pg, Item v1, Item v2)
{
	(*pg)[v1][v2] = 1;
}

int graph_is_adjacent(Graph *pg, Item v1, Item v2)
{
	if ((*pg)[v1][v2] == 1) //Checking adjacency
	{
		return(1);
	}
	else
	{
		return(0);
	}
}

void graph_destroy(Graph *g)
{
	int i;

	for (i = 0; i < N; i++) //frees memory
		free((*g)[i]);
	free(*g);

}