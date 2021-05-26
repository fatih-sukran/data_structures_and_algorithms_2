#include <stdio.h>

// For Weiss example
#define VERTEX_COUNT    5

#define INF    999999999
#define UNKNOWN -1

#define BOOL    int
#define TRUE    1
#define FALSE   0

/* The graph representation from MIT book page 589 */
int graph[VERTEX_COUNT][VERTEX_COUNT] = {
                       //     s    t    y    x    z
                    /*s*/ { INF,   6,   7, INF, INF },
                    /*t*/ { INF, INF,   8,   5,  -4 },
                    /*y*/ { INF, INF, INF,  -3,   9 },
                    /*x*/ { INF,  -2, INF, INF, INF },
                    /*z*/ {   2, INF, INF,   7, INF },

                };


// For Weiss book example
const char* node_names[VERTEX_COUNT] = { "s", "t", "y", "x", "z" };

int costs[VERTEX_COUNT];
int previos_point[VERTEX_COUNT];

void InitializeArrays(int source);
void PrintArrays();
void PrintPath(int start, int target);

BOOL BellmanFordShortestPath(int source);


BOOL BellmanFordShortestPath(int source)
{
    int i, row, column;

    InitializeArrays(source);

    // Main loop
    for (i = 0; i < (VERTEX_COUNT - 1); ++i) {

        // STEP 1-) Check the graph representation to find the edges
        for (row = 0; row < VERTEX_COUNT; ++row)
            for (column = 0; column < VERTEX_COUNT; ++column)
                // Find the edges &  APPLY UPDATE/RELAXATION!
                if (INF != graph[row][column]) {
                    // Apply relaxation/update procedure!
                    if ((costs[row] + graph[row][column]) < costs[column]) {
                        costs[column] = (costs[row] + graph[row][column]);
                        previos_point[column] = row;
                    }
                    //PrintArrays();
                }
        // STEP 2-) Check the graph for negative cost cycle
        for (row = 0; row < VERTEX_COUNT; ++row)
            for (column = 0; column < VERTEX_COUNT; ++column)
                // Find the edges
                if (INF != graph[row][column])
                    // Check part!
                    if ((costs[row] + graph[row][column]) < costs[column])
                        return FALSE;
    }
    return  TRUE;

}

void InitializeArrays(int source)
{
    int i;

    for (i = 0; i < VERTEX_COUNT; ++i) {
        costs[i] = INF;
        previos_point[i] = UNKNOWN;
    }

    costs[source] = 0;
}


void PrintArrays()
{
    int i;

    for (i = 0; i < VERTEX_COUNT; ++i)
        printf("costs[%s]..: %d\n", node_names[i], costs[i]);

    printf("---------------------------\n");

    for (i = 0; i < VERTEX_COUNT; ++i)
        if (-1 == previos_point[i])
            printf("previous_point[%s]..: STARTING VERTEX\n", node_names[i]);
        else
            printf("previous_point[%s]..: %s\n", node_names[i], node_names[previos_point[i]]);
        //printf("previous_point[%d]..: v%d\n", i, previos_point[i]);

    printf("===========================\n");
}

void PrintPath(int start, int target)
{
    /* If the target is NOT equal to starting point call RECURSIVE PrintPath */
    if (start != target)
        PrintPath(start, previos_point[target]);

    /* Print the path items while coming back from BASE CASE */
    printf("%s -> ", node_names[target]);
}


int main()
{
    int start_vertex = 0; // This is the (single) source
    int i;

    if (FALSE == BellmanFordShortestPath(start_vertex)) {
        printf("Your graph has (some) negative cost cycle(s)!\n");
        printf("Bellman-Ford algorithm can NOT be applied to this kind of graphs!");
        printf("Your program will be ended...");
        return 1;
    }

    PrintArrays();

    for (i = 1; i < VERTEX_COUNT; ++i) {
        printf("Destination %s : ", node_names[i]);
        PrintPath(start_vertex, i);
        printf("\n");
    }


    return 0;
}