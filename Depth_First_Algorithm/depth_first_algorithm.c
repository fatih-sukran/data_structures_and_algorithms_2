#include <stdio.h>

#define VERTEX_COUNT 10

#define NOT_VISITED 0
#define VISITED 1

#define ALL_VISITED -1
#define EMPTY -1

//const char* vertex_name[VERTEX_COUNT] = {
//        "Vertex 0",
//        "Vertex 1",
//        //...
//};

/* Example graph from Tondo&Leung&Kruse Book page:580  */
/* This is the adjacency table representation of the example graph */

int graph[VERTEX_COUNT][VERTEX_COUNT] = {

    //  v0 v1 v2 v3 v4 v5 v6 v7 v8 v9
    /*ROW of Vertex 0 */ {0, 1, 0, 0, 0, 1, 0, 0, 0, 0},
    /*ROW of Vertex 1 */ {0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
    /*ROW of Vertex 2 */ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    /*ROW of Vertex 3 */ {0, 0, 1, 0, 1, 0, 0, 1, 1, 0},
    /*ROW of Vertex 4 */ {0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
    /*ROW of Vertex 5 */ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    /*ROW of Vertex 6 */ {1, 1, 1, 0, 0, 0, 0, 0, 0, 0},
    /*ROW of Vertex 7 */ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    /*ROW of Vertex 8 */ {0, 0, 1, 0, 0, 0, 0, 1, 0, 0},
    /*ROW of Vertex 9 */ {0, 0, 0, 0, 1, 0, 0, 0, 0, 0}};

/* We will use this array to check whether a vertex has been visited or not */
int visited[VERTEX_COUNT];

/* We will use this array to put the vertex names as output */
int output[VERTEX_COUNT];

/* All the vertex names will be placed into output array from the and to the beginning */
/* and this variable will be used as the location! */
int output_index;

void PrepareVisitedArray();
void PrepareOutputArray();
int FindUnvisitedNode();
void DepthFirstTopologicalSort(int vertex);
void PrintOutputArray();

void PrepareVisitedArray()
{
    int i;

    for (i = 0; i < VERTEX_COUNT; ++i)
        visited[i] = NOT_VISITED;
}

void PrepareOutputArray()
{
    int i;

    for (i = 0; i < VERTEX_COUNT; ++i)
        output[i] = EMPTY;

    output_index = VERTEX_COUNT - 1;
}

/*
 *
 * This function checks the visited array and tries to find an unvisited vertex index
 * If all the vertices are visited it return ALL_VISITED which is -1
*/
int FindUnvisitedNode()
{
    int i;
    for (i = 0; i < VERTEX_COUNT; ++i)
        if (NOT_VISITED == visited[i])
            return i;

    return ALL_VISITED;
}

/* RECURSIVE Depth First Topological Sort function */
void DepthFirstTopologicalSort(int vertex)
{
    int neighbor;

    /* The first thing is declaring the vertex as VISITED */
    visited[vertex] = VISITED;

    /* Find the unvisited neighbors of the vertex and call this recursive function for them! */
    /* TRICKY PART : Finding the unvisited neigbors */
    for (neighbor = 0; neighbor < VERTEX_COUNT; ++neighbor)
    {
        /* 1 == graph[vertex][column] means we found a neighbor */
        /* AND */
        /* NOT_VISITED == visited[column] means that neighbor is UNVISITED */
        if ((1 == graph[vertex][neighbor]) && (NOT_VISITED == visited[neighbor]))
            DepthFirstTopologicalSort(neighbor);
    }

    /* Output the vertex. Because we have nothing else to do here... */
    output[output_index] = vertex;
    /* To locate the next item we need to decrease the output index because we are locating
       the items from end to the beginning of the output array */
    --output_index;
}

void PrintOutputArray()
{
    int i;
    for (i = 0; i < VERTEX_COUNT; ++i)
        printf("V%d --> ", output[i]);

    printf("\n");
}

int main()
{
    int node;

    // Ensure that the visited array initialized as UNVISITED for all nodes/vertices
    PrepareVisitedArray();

    // The output array will be used for the output starting from end to the beginning!
    PrepareOutputArray();

    /* This loop will work UNTIL all the vertices become VISITED */
    node = FindUnvisitedNode();
    while (ALL_VISITED != node)
    {
        /* If we are here this means we found an unvisited node */
        /* And we will start a recursive call for that node! */
        DepthFirstTopologicalSort(node);
        node = FindUnvisitedNode();
    }

    PrintOutputArray();

    return 0;
}