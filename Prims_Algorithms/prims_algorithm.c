#include <stdio.h>

// For Weiss example
#define VERTEX_COUNT    5

#define INF    999999999

#define UNKNOWN -1
#define KNOWN   1

#define NOT_FOUND   -1

int graph[VERTEX_COUNT][VERTEX_COUNT] = {
                       //     v0   v1   v2   v3   v4
                    /*v0*/ { INF,   5,   3, INF,   2 },
                    /*v1*/ { INF, INF,   2,   6, INF },
                    /*v2*/ { INF,   1, INF,   2, INF },
                    /*v3*/ { INF, INF, INF, INF, INF },
                    /*v4*/ { INF,   6,  10,   4, INF },

                };

// For Weiss book example
const char* node_names[VERTEX_COUNT] = { "V1", "V2", "V3", "V4", "V5"};


int known[VERTEX_COUNT];
int costs[VERTEX_COUNT];
int previos_point[VERTEX_COUNT];


void PrimsMST(int start);
void InitializeArrays();
int FindSmallestCostVertexAmongUnknowns();
void PrintArrays();
//void PrintPath(int start, int target);

void InitializeArrays()
{
    int i;

    for (i = 0; i < VERTEX_COUNT; ++i) {
        known[i] = UNKNOWN;
        costs[i] = INF;
        previos_point[i] = UNKNOWN;
    }
}


int FindSmallestCostVertexAmongUnknowns()
{
    int i;
    int smallest = INF;
    int smallest_index = NOT_FOUND;

    for (i = 0; i < VERTEX_COUNT; ++i) {
        if (UNKNOWN == known[i] && costs[i] < smallest) {
            smallest_index = i;
            smallest = costs[i];
        }
    }

    return  smallest_index;
}

void PrimsMST(int source)
{
    int vertex;
    int neighbor;

    costs[source] = 0;

    vertex = FindSmallestCostVertexAmongUnknowns();
    printf("The first vertex chosen is %d\n", vertex);

    while (NOT_FOUND != vertex) {
        known[vertex] = KNOWN;

        // To see the steps of algorithm display the arrays
        printf("After vertex %d has been declared as known.\n", vertex);
        PrintArrays();

        /* Check the unknown neighbors and update their costs if possible!
         * possible means if it becomes better!
        */
        for (neighbor = 0; neighbor < VERTEX_COUNT; ++neighbor) {
            // Find an unknown neighbor of vertex
            if ((INF != graph[vertex][neighbor]) &&  (UNKNOWN == known[neighbor]))
                // UPDATE PROCEDURE
                // If you find a neighbor try to update its cost if you have a better (INDIRECT) cost
                if ( (graph[vertex][neighbor]) < costs[neighbor]) {
                    costs[neighbor] = graph[vertex][neighbor];
                    previos_point[neighbor] = vertex;
                }
        }

        vertex = FindSmallestCostVertexAmongUnknowns();
    }

}

void PrintArrays()
{
    int i;

    for (i = 0; i < VERTEX_COUNT; ++i)
        printf("known[%d]..: %d\n", i, known[i]);

    printf("---------------------------\n");

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

//void PrintPath(int start, int target)
//{
//    /* If the target is NOT equal to starting point call RECURSIVE PrintPath */
//    if (start != target)
//        PrintPath(start, previos_point[target]);

//    /* Print the path items while coming back from BASE CASE */

//    printf("%s -> ", node_names[target]);


//    /* For Weiss Book example */
////    printf("V%d -> ", target + 1);

//    /* For Tondo Book example */
//    //printf("V%d -> ", target);
//}


int main()
{
    int start_vertex = 0; // This is the (single) source

    InitializeArrays();

    PrimsMST(start_vertex);

    PrintArrays();

    return 0;
}