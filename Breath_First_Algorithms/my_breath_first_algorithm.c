#include <stdio.h>
#include <stdlib.h>

#define VERTEX_COUNT 10

#define VISITED 1
#define NOT_VISITED 0

typedef struct Queue {
    int vertex;
    struct Queue *next;
}Queue;

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
int isVisited[VERTEX_COUNT];
int predecessorCount[VERTEX_COUNT];

void assignZero(int* array) {
    int i;
    for(i = 0; i < VERTEX_COUNT; ++i) {
        array[i] = NOT_VISITED;
    }
}

void preparePredecessorCount() {
    assignZero(predecessorCount);

    int i, j;
    for(i = 0; i < VERTEX_COUNT; ++i) {
        for(j = 0; j < VERTEX_COUNT; ++j) {
            if(graph[i][j] == 1) {
                predecessorCount[j]++;
            }
        }
    }
}

int enQueue(Queue* first, Queue *last, int vertex) {
    Queue* temp = (Queue*) malloc(sizeof(Queue));
    temp->vertex = vertex;
    temp->next = NULL;
    if (last == NULL) {
        first = temp;
        last = temp;
    }else {
        last->next = temp;
        last = last->next;
    }
}


void putQueueNonPredeccessor(Queue* first, Queue* last) {
    int i;
    for(i = 0; i < VERTEX_COUNT; ++i) {
        if(predecessorCount[i] == 0) {
            enQueue(first, last, i);
        }
    }
}

int deQueue(Queue* first, Queue *last) {
    if (first == NULL) {
        return 0;
    } else if (first->next = NULL) {
        first = first->next;
        last = first;
    } else {
        first = first->next;
    }
}

int main() {
    Queue* first = NULL;
    Queue* last = NULL;

    assignZero(isVisited);
    preparePredecessorCount();
    putQueueNonPredeccessor(first, last);

    while (first != NULL)
    {
        printf("%d -> ", last->vertex);
    }
}