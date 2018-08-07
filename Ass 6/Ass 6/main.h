
#define N 100

typedef int **Graph;
typedef int Item;

int graph_is_adjacent(Graph *pg, Item v1, Item v2);
void graph_destroy(Graph *g);
void graph_init(Graph *graph); // initialize graph
void graph_insert_edge(Graph *pg, Item v1, Item v2);

