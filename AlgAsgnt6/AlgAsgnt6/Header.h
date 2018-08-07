//Algorithms Assignment 6 - Graphs - Header
//Oct. 30, 2016
//Creates list of nodes and connections


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include<conio.h>

#define N 100 //Number of nodes

typedef int **Graph;
typedef int Item;

//prototypes
void graph_init(Graph *graph); // initialize graph
void graph_insert_vertex(Graph *graph);
void graph_insert_edge(Graph *pg, Item v1, Item v2);
int graph_is_adjacent(Graph *pg, Item v1, Item v2);
void graph_destroy( Graph *g );