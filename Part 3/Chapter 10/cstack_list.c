#include <stdio.h>
#include <stdlib.h>

#include "cstack_list.h"

struct Node
{
    ElementType Elem;
    PtrToNode Next;
};

int IsEmpty(Stack s)
{
    return s->Next == NULL;
}

Stack CreateStack(void)
{
    Stack s;

    s = (Stack)malloc(sizeof(struct Node));
    if (s == NULL)
    {
        perror("Out of space\n");
        exit(1);
    }
    s->Next = NULL;
    MakeEmpty(s);
    return s;
}

void DisposeStack(Stack s)
{
    if (s->Next != NULL)
    {
        MakeEmpty(s);
    }
    free(s);
}

void MakeEmpty(Stack s)
{
    if (s == NULL)
        printf("You must use CreateStack() first\n");
    else
        while (!IsEmpty(s))
            Pop(s);
}

void Push(ElementType elem, Stack s)
{
    PtrToNode temp;

    temp = (PtrToNode)malloc(sizeof(struct Node));
    if (temp == NULL)
    {
        perror("Out of space");
        exit(1);
    }
    else
    {
        temp->Elem = elem;
        temp->Next = s->Next;
        s->Next = temp;
    }
}

ElementType Top(Stack s)
{
    if (!IsEmpty(s))
        return s->Next->Elem;
    printf("Empty stack");
    return 0;
}

void Pop(Stack s)
{
    PtrToNode first;

    if (IsEmpty(s))
        printf("Empty stack");
    else
    {
        first = s->Next;
        s->Next = s->Next->Next;
        free(first);
    }
}