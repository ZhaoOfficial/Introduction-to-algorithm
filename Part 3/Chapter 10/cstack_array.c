#include <stdio.h>
#include <stdlib.h>

#include "cstack_array.h"

#define EmptyTOS -1
#define MinStackSize 5

struct StackRecord
{
    int Capacity;
    int TopOfStack;
    ElementType *Array;
};

int IsEmpty(Stack s)
{
    return s->TopOfStack == EmptyTOS;
}

int IsFull(Stack s)
{
    return s->TopOfStack == s->Capacity;
}

Stack CreateStack(int MaxElements)
{
    Stack s;

    if (MaxElements < MinStackSize)
        MaxElements = MinStackSize;
    s = (Stack)malloc(sizeof(struct StackRecord));
    if (s == NULL)
    {
        perror("Out of space\n");
        exit(1);
    }

    s->Array = (ElementType *)malloc(MaxElements * sizeof(ElementType));
    if (s->Array == NULL)
    {
        perror("Out of space\n");
        exit(1);
    }
    s->Capacity = MaxElements;
    MakeEmpty(s);

    return s;
}

void DisposeStack(Stack s)
{
    if (s != NULL)
    {
        free(s->Array);
        free(s);
    }
}

void MakeEmpty(Stack s)
{
    s->TopOfStack = EmptyTOS;
}

void Push(ElementType elem, Stack s)
{
    if (IsFull(s))
        printf("Stack overflow\n");
    else
        s->Array[++(s->TopOfStack)] = elem;
}

ElementType Top(Stack s)
{
    if (!IsEmpty(s))
        return s->Array[s->TopOfStack];
    printf("Empty stack\n");
    return 0;
}

void Pop(Stack s)
{
    if (IsEmpty(s))
        printf("Stack underflow\n");
    else
        s->TopOfStack--;
}

ElementType TopAndPop(Stack s)
{
    if (!IsEmpty(s))
        return s->Array[(s->TopOfStack)--];
    printf("Empty stack\n");
    return 0;
}