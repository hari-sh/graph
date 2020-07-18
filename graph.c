#include "list.h"

struct Graph 
{ 
	int V; 
	gen_list** array; 
}; 

struct Graph* createGraph(int V) 
{ 
	struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph)); 
	graph->V = V; 

    graph->array = (gen_list**)malloc(V * sizeof(gen_list)); 
  
	int i; 
	for (i = 0; i < V; i++) 
		graph->array[i] = gen_list_create(sizeof(int)); 

	return graph; 
} 

void addEdge(struct Graph* graph, int src, int dest) 
{ 
    gen_list_push((graph->array[src]), &dest);
    gen_list_push((graph->array[dest]), &src);
} 

void print_vertex(void* vert)    {
    printf("%d  ", *(int*)vert);
}
void printGraph(struct Graph* graph) 
{ 
	int v; 
	for (v = 0; v < graph->V; ++v) 
	{ 
        printf("vertex %d........",v);
		gen_list_print((graph->array[v]), print_vertex);
	} 
} 

void main() 
{
	struct Graph* graph = createGraph(5); 
    
	addEdge(graph, 0, 1); 
	addEdge(graph, 0, 4); 
	addEdge(graph, 1, 2); 
	addEdge(graph, 1, 3); 
	addEdge(graph, 1, 4); 
	addEdge(graph, 2, 3); 
	addEdge(graph, 3, 4); 
    
	printGraph(graph); 
} 
