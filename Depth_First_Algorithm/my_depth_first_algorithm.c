#include <stdio.h>
#include <stdlib.h>

#define VERTEX_COUNT 10

#define VISETED 1
#define NOT_VISETED 0

int isViseted[VERTEX_COUNT];
int graph[VERTEX_COUNT][VERTEX_COUNT] = {
    {0, 1, 0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 0, 1, 0, 0, 1, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 1, 1, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0, 0, 0}
};

void prepareIsVisited() {
    int i;
    for(i = 0; i < VERTEX_COUNT; ++i) {
        isViseted[i] = NOT_VISETED;
    }
}

void DFS(int vertex) {
    isViseted[vertex] = VISETED;
    printf("%d -> ", vertex); //OUTPUT: 0 -> 1 -> 7 -> 5 -> 2 -> 3 -> 4 -> 8 -> 6 -> 9 ->
    int i;
    for(i = 0; i < VERTEX_COUNT; ++i) {
        if (isViseted[i] == NOT_VISETED && graph[vertex][i] == 1) {
            DFS(i);
        }
    }
}

int main() {
    prepareIsVisited();
    int i;
    for(i = 0; i < VERTEX_COUNT; ++i) {
        if(isViseted[i] == NOT_VISETED) {
            DFS(i);
        }
    }
}