#include <stdio.h>
#include <string.h>

#define TABLE_SIZE 11

#define TRUE    1
#define FALSE   0

typedef int BOOL;

/* Data will be stored in Hash Table */
typedef struct tagKeyValue{
    char* key;
    char* value;
}KeyValuePair;

/* GLOBAL Hash Table */
KeyValuePair* hashTable[TABLE_SIZE];

int itemCount;


int HashFunction(char* key);
BOOL DoHashingWithLinearProbing(KeyValuePair *data);


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

BOOL DoHashingWithLinearProbing(KeyValuePair* data)
{
    int index;
    int step = 1;

    index = HashFunction(data->key);

    // Check whether the index is occupied or not
    // If it is occupied APPLY linear probing!
    // Check the next slot in a CIRCULAR FASHION!
    while (0 != hashTable[index] && step != TABLE_SIZE) {
        index = (index + 1) % TABLE_SIZE;
        ++step;
    }

    // We FOUND an empty slot
    if (0 == hashTable[index]) {
        hashTable[index] = data;
        return TRUE;
    } else // The table was FULL! We could NOT find an empty slot!
        return FALSE;
}

BOOL DoHashingWithQuadraticProbing(KeyValuePair* data)
{
    int index;
    int step = 1;
    double loadFactor = 0.0;

    index = HashFunction(data->key);
    loadFactor = (double)itemCount / TABLE_SIZE;

    // Check whether the index is occupied or not
    // If it is occupied APPLY linear probing!
    // Check the next slot in a CIRCULAR FASHION!
    while (loadFactor < 0.7 && 0 != hashTable[index]) {
        index = (index + (step * step)) % TABLE_SIZE;
        ++step;
    }

    // We FOUND an empty slot
    if (0 == hashTable[index]) {
        hashTable[index] = data;
        ++itemCount;
        return TRUE;
    } else { // The table is at least HALF FULL!
        //It means quadratic may fail to find an empty place!
        printf("Table's load factor is %lf and it is bigger than or equal to 0.5!\n", loadFactor);
        printf("Quadratic probing can not be applied while load factor is equal to or bigger than 0.5!\n");
        return FALSE;
    }
}


void PrintHashTable()
{
    int i;

    for (i = 0; i < TABLE_SIZE; ++i)
        if (0 != hashTable[i])
            printf("hashTable[%d] --> %s:%s\n", i, hashTable[i]->key, hashTable[i]->value);
        else
            printf("hashTable[%d] --> EMPTY\n", i);
}



int main()
{
//    KeyValuePair p1;
//    p1.key = "a";
//    p1.value = "b";
//    DoHashingWithLinearProbing(&p1);


//    KeyValuePair p2;
//    p2.key = "c";
//    p2.value = "d";
//    DoHashingWithLinearProbing(&p2);


//    KeyValuePair p3;
//    p3.key = "e";
//    p3.value = "f";
//    DoHashingWithLinearProbing(&p3);

//    KeyValuePair p4;
//    p4.key = "e";
//    p4.value = "g";
//    DoHashingWithLinearProbing(&p4);

//    KeyValuePair p5;
//    p5.key = "e";
//    p5.value = "h";
//    DoHashingWithLinearProbing(&p5);

//    PrintHashTable();


    KeyValuePair p1;
    p1.key = "a";
    p1.value = "b";
    DoHashingWithQuadraticProbing(&p1);


    KeyValuePair p2;
    p2.key = "c";
    p2.value = "d";
    DoHashingWithQuadraticProbing(&p2);


    KeyValuePair p3;
    p3.key = "e";
    p3.value = "f";
    DoHashingWithQuadraticProbing(&p3);

    KeyValuePair p4;
    p4.key = "g";
    p4.value = "h";
    DoHashingWithQuadraticProbing(&p4);

    KeyValuePair p5;
    p5.key = "k";
    p5.value = "l";
    DoHashingWithQuadraticProbing(&p5);

    KeyValuePair p6;
    p6.key = "m";
    p6.value = "n";
    DoHashingWithQuadraticProbing(&p6);

    KeyValuePair p7;
    p7.key = "m";
    p7.value = "o";
    DoHashingWithQuadraticProbing(&p7);

    PrintHashTable();



    return 0;
}