#include <stdio.h>
#include <stdlib.h>
#include "c_hashtable_list.h"

#define MinTableSize 5

struct ListNode
{
    ElementType Elem;
    Position Next;
};

typedef Position List;

static void DeleteList(List list)
{
    Position pos, temp;

    pos = list->Next;
    list->Next = NULL;
    while (pos != NULL)
    {
        temp = pos->Next;
        free(pos);
        pos = temp;
    }
}

static size_t Hash(ElementType elem, size_t TableSize)
{
    size_t HashVal = 0;

    while (elem > 1.0)
    {
        HashVal = HashVal * 7793843 + elem;
        elem /= 10.0;
    }

    return HashVal % TableSize;
}

/* List *HashTableList will be an array of List */
/* The lists use headers */
struct HashTableBase
{
    size_t TableSize;
    List *HashTableList;
};

HashTable InitializeTable(size_t TableSize)
{
    HashTable h;
    int i;

    if (TableSize < MinTableSize)
        TableSize = MinTableSize;

    h = (HashTable)malloc(sizeof(struct HashTableBase));
    if (h == NULL)
    {
        perror("Out of space\n");
        exit(1);
    }

    h->TableSize = TableSize;

    h->HashTableList = (List *)malloc(sizeof(List) * h->TableSize);
    if (h->HashTableList == NULL)
    {
        perror("Out of space\n");
        exit(1);
    }

    for (i = 0; i < h->TableSize; i++)
    {
        h->HashTableList[i] = (List *)malloc(sizeof(struct ListNode));
        if (h->HashTableList[i] == NULL)
        {
            perror("Out of space\n");
            exit(1);
        }
        else
            h->HashTableList[i]->Next = NULL;
    }

    return h;
}

void DestroyTable(HashTable h)
{
    int i;

    for (i = 0; i < h->TableSize; i++)
    {
        DeleteList(h->HashTableList[i]);
    }
}

Position Find(ElementType elem, HashTable h)
{
    Position pos;
    List l;

    l = h->HashTableList[Hash(elem, h->TableSize)];
    pos = l->Next;
    while (pos != NULL && pos->Elem != elem)
        pos = pos->Next;

    return pos;
}

ElementType Retrieve(Position pos)
{
    return pos->Elem;
}

void Insert(ElementType elem, HashTable h)
{
    Position pos, NewPos;
    List l;

    pos = Find(elem, h);
    if (pos == NULL)
    {
        NewPos = (Position)malloc(sizeof(struct ListNode));
        if (NewPos == NULL)
        {
            perror("Out of space\n");
            exit(1);
        }
        else
        {
            l = h->HashTableList[Hash(elem, h->TableSize)];
            NewPos->Next = l->Next;
            NewPos->Elem = elem;
            l->Next = NewPos;
        }
    }
}

/* next prime of this number */
int NextPrime(int number) {
    return 97;
}