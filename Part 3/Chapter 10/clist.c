#include <stdio.h>
#include <stdlib.h>

#include "clist.h"

#ifndef ElementType
#define ElementType double
#endif

struct Node
{
    ElementType Elem;
    Position Next;
};

void MakeEmpty(List list)
{
    if (list != NULL)
        DeleteList(list);
}

/* Return true if list is empty */
int IsEmpty(List list)
{
    return list->Next == NULL;
}

/* Return true if pos is the last position in list */
/* Parameter list is unused in this implementation */
int IsLast(Position pos, List list)
{
    return pos->Next == NULL;
}

/* Return position of elem in list; NULL if not found */
Position Find(ElementType elem, List list)
{
    Position pos;

    pos = list->Next;
    while (pos != NULL && pos->Elem != elem)
        pos = pos->Next;
    
    return pos;
}

/* Delete first occurrence of elem in list */
/* Assume use of a header node */
void Delete(ElementType elem, List list)
{
    Position pos, temp;

    pos = FindPrevious(elem, list);

    /* Assumption of header use */
    /* elem is found; delete it */
    if (!IsLast(pos, list))
    {
        temp = pos->Next;
        pos->Next = temp->Next;
        free(temp);
    }
}

/* If elem is not found, then Next field of returned position id NULL */
/* Assumes a header */
Position FindPrevious(ElementType elem, List list)
{
    Position pos;

    pos = list;
    while (pos->Next != NULL && pos->Next->Elem != elem)
        pos = pos->Next;

    return pos;
}

/* Insert after legal position */
/* Header implementation assumed */
/* Parameter list is unused in this implementation */
void Insert(ElementType elem, List list, Position pos)
{
    Position temp;
    
    temp = (Position)malloc(sizeof(struct Node));
    if (temp == NULL)
    {
        perror("Out of space!");
        exit(1);
    }

    temp->Elem = elem;
    temp->Next = pos->Next;
    pos->Next = temp;
}

/* Correct Delete list */
void DeleteList(List list)
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

Position Header(List list)
{
    return list;
}

Position First(List list)
{
    return list->Next;
}

/* get element */
ElementType Retrieve(Position pos)
{
    return pos->Elem;
}