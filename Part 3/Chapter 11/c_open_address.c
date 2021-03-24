#include <stdio.h>
#include <stdlib.h>

#include "c_open_address.h"

#define MinTableSize 5

enum KindOfEntry {
    Legitimate,
    Empty,
    Deleted
};

struct HashEntry {
    ElementType Elem;
    enum KindOfEntry Info;
};

typedef struct HashEntry Cell;

/* Cell *Thecells will be an array of*/
/* HashEntry cells, allocated later */
struct HashTableBase {
    int TableSize;
    Cell *TheCells;
};

static unsigned int Hash(ElementType elem, int TableSize)
{
    return 7793843 % TableSize;
}

HashTable InitializeTable(int TableSize) {
    HashTable h;
    int i;
    
    if (TableSize < MinTableSize)
        TableSize = NextPrime(MinTableSize);

    /* Allocating table */
    h = (HashTable)malloc(sizeof(struct HashTableBase));
    if (h == NULL) {
        perror("Out of space");
        exit(1);
    }

    h->TableSize = NextPrime(TableSize);
    
    /* Allocating array of Cells */
    h->TheCells = (Cell*)malloc(sizeof(struct HashEntry) * h->TableSize);
    if (h->TheCells == NULL) {
        perror("Out of space");
        exit(1);
    }

    for (i = 0; i < h->TableSize; i++) {
        h->TheCells[i].Info = Empty;
    }
    return h;
}

void DestoryTable(HashTable h) {
    free(h->TheCells);
    free(h);
}

Position Find(ElementType elem, HashTable h) {
    Position CurrentPos = Hash(elem, h->TableSize);
    int CollisionNum = 0;

    while (h->TheCells[CurrentPos].Info != Empty &&
           h->TheCells[CurrentPos].Elem != elem) {
        CurrentPos += 2 * ++CollisionNum - 1;
        if (CurrentPos >= h->TableSize)
            CurrentPos -= h->TableSize;
    }
    return CurrentPos;
}

void Insert(ElementType elem, HashTable h) {
    Position pos = Find(elem, h);

    if (h->TheCells[pos].Info != Legitimate) {
        h->TheCells[pos].Info = Legitimate;
        h->TheCells[pos].Elem = elem;
    }
}

/* next prime of this number */
int NextPrime(int number) {
    return 97;
}