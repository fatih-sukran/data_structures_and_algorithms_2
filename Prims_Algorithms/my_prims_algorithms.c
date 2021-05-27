#include <stdio.h>

#define VERTEX_COUNT 5

#define KNOWN 1
#define UNKNOWN -1

#define NOT_FOUND -1

#define INF 99999

int known[VERTEX_COUNT];
int previous_vertex[VERTEX_COUNT];
int costs[VERTEX_COUNT];
int graph[VERTEX_COUNT][VERTEX_COUNT] = {
    {INF,   5,   3, INF,   2},
    {INF, INF,   2,   6, INF},
    {INF,   1, INF,   2, INF},
    {INF, INF, INF, INF, INF},
    {INF,   6,  10,   4, INF},
};

const char* node_names[VERTEX_COUNT] = { "V0", "V1", "V2", "V3", "V4" };

void initializeArrays()
{
    int i;
    for (i = 0; i < VERTEX_COUNT; i++)
    {
        known[i] = UNKNOWN;
        previous_vertex[i] = UNKNOWN;
        costs[i] = INF;
    }
}

int findMinCostIndex()
{
    int min = INF;
    int index = NOT_FOUND;
    int i;

    for (i = 0; i < VERTEX_COUNT; i++)
    {
        if (known[i] == UNKNOWN && costs[i] < min)
        {
            min = costs[i];
            index = i;
        }
    }
    return index;
}

void Dijkstras(int source)
{
    int vertex;

    costs[source] = 0;
    vertex = findMinCostIndex();

    while (vertex != NOT_FOUND)
    {

        known[vertex] = KNOWN;
        int i;
        for (i = 0; i < VERTEX_COUNT; i++)
        {
            if (known[i] == UNKNOWN && graph[vertex][i] != INF)
            if (costs[i] > graph[vertex][i]) {
                costs[i] = graph[vertex][i];
                previous_vertex[i] = vertex;
            }
        }
        vertex = findMinCostIndex();
    }
}

void printArrays()
{
    int i;
    for (i = 0; i < VERTEX_COUNT; i++)
        printf("costs[%d] : %d\n", i, costs[i]);
        
    for (i = 0; i < VERTEX_COUNT; i++)
        printf("previous_vertex[%d] : %d\n", i, previous_vertex[i]);
        
    for (i = 0; i < VERTEX_COUNT; i++)
        printf("known[%d] : %d\n", i, known[i]);
    
}

void PrintPath(int start, int target)
{
    if (start != target)
        PrintPath(start, previous_vertex[target]);

    printf("%s -> ", node_names[target]);
}

int main()
{
    int source = 0;

    initializeArrays();
    Dijkstras(source);
    printArrays();
    PrintPath(source, 1);
}