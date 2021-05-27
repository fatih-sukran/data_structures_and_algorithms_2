#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TABLE_SIZE  11

#define ENGLISH_ALPHABET_SIZE   26


//#define NULL    (void*)0

/* This is the data that we will store in a hash table! */
typedef struct tagStudent {
    int id;
    char* name;
    char* surname;// This will be our key!
    // ...
}Student;

/* This is the structure to implement separate chaining */
typedef struct tagSingleLinkedList {
    Student* data;
    struct tagSingleLinkedList* next;
}SLL;

/* SLL related functions */
SLL* AddFront(SLL* list, Student* data);
void PrintList(SLL* list);

/* Separate Chaining related functions */
int HashFunction(char* key);
void PrintHashTable(SLL** pTable);
void DoHashingWithLinearProbing(SLL **pTable, Student* pData);

/* UTILITY FUNCTIONS */

/* Random data generation functions */
int GenerateRandomInt(int max);
char GenerateRandomChar();
char* GenerateRandomString(int maxStringLength);

/* Student data function */
void PrintStudent(Student* pStudent);


/* SEPARATE CHAINING RELATED FUNCTION IMPLEMENTATIONS  */

void DoHashingWithLinearProbing(SLL** pTable, Student* pData)
{
    int index;

    index = HashFunction(pData->surname);
    pTable[index] = AddFront(pTable[index], pData);
}


int HashFunction(char* key)
{
    int length;
    int i, total;

    length = strlen(key);

    total = 0;
    for (i = 0; i < length; ++i)
        total += (int) key[i];// Each character's ASCII table index will be summed-up

    // Obtain an index between [0..(TABLE_SIZE-1)]
    return (total % TABLE_SIZE);
}

void PrintHashTable(SLL** pTable)
{
    int i;

    for (i = 0; i < TABLE_SIZE; ++i) {
        printf("Hash Table[%d] list --> ", i);
        PrintList(pTable[i]);
        printf("------------------------------\n");
    }

}


/* SINGLE LINKED LIST RELATED FUNCTION IMPLEMENTATIONS  */

SLL* AddFront(SLL* list, Student* data)
{
    SLL* pNewItem;

    pNewItem = (SLL*) malloc(sizeof(SLL));
    if (0 == pNewItem) {
        fprintf(stderr, "Cannot Allocate memory!!!\n");
        exit(EXIT_FAILURE);
    }
    pNewItem->data = data;
    pNewItem->next = list;

    return  pNewItem;
}

// Simple RECURSIVE PrintList function!
void PrintList(SLL* list)
{
    if (0 != list) {
        PrintStudent(list->data);
        PrintList(list->next);
    } else
        printf("Empty list...\n");
}

int GenerateRandomInt(int max)
{
    return (rand() % max);
}

char GenerateRandomChar()
{
    int number;

    // Obtain a number between [0..25]
    number = GenerateRandomInt(ENGLISH_ALPHABET_SIZE);
    return ((char)('a' + number));
}

char* GenerateRandomString(int maxStringLength)
{
    int length, i;
    char* pData;

    length = GenerateRandomInt(maxStringLength) + 1;
    pData = malloc(sizeof(char) * (length + 1) ); // +1 for NULL

    for (i = 0; i < length; ++i)
        pData[i] = GenerateRandomChar();

    // Add NULL to the end of the string
    pData[i] = '\0';

    printf("GenerateRandomString --> Genrated random string is %s\n", pData);
    return pData;
}

void PrintStudent(Student* pStudent)
{
    printf("Student ID : %d\n", pStudent->id);
    printf("Student Name : %s\n", pStudent->name);
    printf("Student Surname : %s\n", pStudent->surname);
}


int main()
{
    SLL* hashTable[TABLE_SIZE];
    //SLL** hashTable = malloc(TABLE_SIZE * sizeof(SLL*));
    int i, dataCount;

    srand(time(0));

    for (i = 0; i < TABLE_SIZE; ++i)
        hashTable[i] = 0;

//    Student st1;
//    st1.id = 100;
//    st1.name = "a";
//    st1.surname = "a";
//    DoHashing(hashTable, &st1);

//    Student st2;
//    st2.id = 200;
//    st2.name = "b";
//    st2.surname = "b";
//    DoHashing(hashTable, &st2);

//    Student st3;
//    st3.id = 300;
//    st3.name = "c";
//    st3.surname = "c";
//    DoHashing(hashTable, &st3);
    Student* pData;
    dataCount = GenerateRandomInt(5) + 1;
    printf("Random data count : %d\n", dataCount);

    for (i = 0; i < dataCount; ++i) {
        pData = (Student*) malloc(sizeof(Student));
        if (0 == pData) {
            fprintf(stderr, "Cannot allocate memory for random data...\n");
            exit(EXIT_FAILURE);
        }
        pData->id = GenerateRandomInt(100);// ID -->  [0 .. 99]
        pData->name = GenerateRandomString(10); // Name length will be [1..10]
        pData->surname = GenerateRandomString(10);// Surname length will be [1..10]

        printf("Randomly generated data which will be inserted into HASH TABLE...\n");
        PrintStudent(pData);

        DoHashingWithLinearProbing(hashTable, pData);
    }

    PrintHashTable(hashTable);

    return 0;
}