#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 11

typedef enum HashType{
    hashWithId,
    hashWithName,
    hashWithSurname
}HashType;

typedef struct tagStudent{
    int id;
    char* name;
    char* surname;
}Student;

typedef struct singleLinkedList{
    Student* student;
    struct singleLinkedList* next;
}SLL;

SLL* hashTable[TABLE_SIZE];

int hashing(Student* student, HashType hashType);
int hashString(char* string);
void prepareHashTable();
SLL* addFront(SLL* list, Student* student);
void separateChaining(Student* student);
void printHashTable();

int main() {
    int i;
    
    for(i = 0; i < 68; i++) {
        Student* student = (Student*) malloc(sizeof(Student));
        student->id = i;
        student->name = "amak";
        student->surname = "amak";
        separateChaining(student);
    }
    printHashTable();
}

int hashing(Student* student, HashType hashType) {
    int hash;
    switch (hashType) {
        case hashWithId:
            hash = student->id % TABLE_SIZE;
            break;
        case hashWithName:
            hash = hashString(student->name);
            break;
        case hashWithSurname:
            hash = hashString(student->surname);
            break;
        default:
            fprintf(stderr, "Unexpecting error!!!");
            break;
    }
    return hash;
}

int hashString(char* string) {
    int total = 0;
    int i;
    int len = strlen(string);

    for(i = 0; i < len; i++) {
        total += (int) string[i];
    }

    return total % TABLE_SIZE;
}

void prepareHashTable() {
    int i;
    
    for(i = 0; i < TABLE_SIZE; i++) 
        hashTable[i] = NULL;
}

SLL* addFront(SLL* list, Student* student) {
    SLL* pNewItem = NULL;

    pNewItem = (SLL*) malloc(sizeof(SLL));
    if (pNewItem == NULL) {
        fprintf(stderr, "memory could not allocat");
        exit(EXIT_FAILURE);
    }

    pNewItem->next = list;
    pNewItem->student = student;

    return pNewItem;
}

void separateChaining(Student* student) {
    int hash;

    hash = hashing(student, hashWithId);
    hashTable[hash] = addFront(hashTable[hash], student);
}

void printHashTable() {
    int i;

    for(i = 0; i < TABLE_SIZE; i++) {
        SLL* sll = hashTable[i];
        printf("HashTable[%d]\n",i);
        printf("===========================================\n");
        while (sll->next != NULL) {
            printf("\tId: %d\n", sll->student->id);
            //printf("\tName: %s\n", sll->student->name);
            //printf("\tSurname: %s\n", sll->student->surname);

            sll = sll->next;
        }
    }
}
