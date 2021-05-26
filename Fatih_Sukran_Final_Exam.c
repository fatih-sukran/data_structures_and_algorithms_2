#include<stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct tagStudent {
   int id;
   char* name;
   char* surname;
}Student;

typedef struct tagSingleLinkedList {
   Student* data;
   struct tagSingleLinkedList* next;
}SLL;


#define TABLE_SIZE 13

int hash(Student* student) {
    int total = 0;
    int len = strlen(student->surname);
    int i;

    for(i = 0; i < len; i++) {
        total += (int) student->surname[i];
    }

    return total % 13;
}

SLL* addFront(SLL* sll, Student* student)
{
    SLL* newSll;

    newSll = (SLL*) malloc(sizeof(SLL));
    if (NULL == newSll) {
        fprintf(stderr, "Memory Cannot Allocate!!!\n");
        exit(EXIT_FAILURE);
    }
    newSll->data = student;
    newSll->next = sll;

    return  newSll;
}

void DoHashing(SLL** sll, Student* student)
{
    int index;

    index = hash(student);
    sll[index] = AddFront(sll[index], student);
}

int main() {
    int i;
    
    for(i = 0; i < 68; i++) {
        Student* student = (Student*) malloc(sizeof(Student));
        student->id = i;
        student->name = "amak";
        student->surname = "amak";
        //separateChaining(student);
    }
    //printHashTable();
}