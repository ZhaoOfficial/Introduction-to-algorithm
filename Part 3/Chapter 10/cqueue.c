#include <stdio.h>
#include <stdlib.h>

#include "cqueue.h"

#define MinQueueSize 5

struct QueueRecord
{
    int Capacity;
    int Front;
    int Rear;
    int Size;
    ElementType *Array;
};

int IsEmpty(Queue q)
{
    return q->Size == 0;
}

int IsFull(Queue q)
{
    return q->Size + 1 == q->Capacity;
}

Queue CreateStack(int MaxElements)
{
    Queue q;

    if (MaxElements < MinQueueSize)
        MaxElements = MinQueueSize;
    q = (Queue)malloc(sizeof(struct QueueRecord));
    if (q == NULL)
    {
        perror("Out of space\n");
        exit(1);
    }

    q->Array = (ElementType *)malloc(MaxElements * sizeof(ElementType));
    if (q->Array == NULL)
    {
        perror("Out of space\n");
        exit(1);
    }
    q->Capacity = MaxElements;
    MakeEmpty(q);

    return q;
}

void DisposeStack(Queue q)
{
    if (q != NULL)
    {
        free(q->Array);
        free(q);
    }
}

void MakeEmpty(Queue q)
{
    q->Size = 0;
    q->Front = 0;
    q->Rear = 1;
}

static int Increment(int value, Queue q)
{
    return (value + 1) % q->Capacity;
}

static int Decrement(int value, Queue q)
{
    return (value + q->Capacity - 1) % q->Capacity;
}


void Enqueue(ElementType elem, Queue q)
{
    if (IsFull(q))
        printf("Queue overflow\n");
    else
    {
        q->Size++;
        q->Array[q->Rear] = elem;
        q->Rear = Increment(q->Rear, q);
    }
}

ElementType Front(Queue q)
{
    if (!IsEmpty(q))
    {
        q->Front = Decrement(q->Front, q);
        return q->Array[increment(q->Front)];
    }
    printf("Empty Queue\n");
    return 0;
}

void Dequeue(Queue q)
{
    if (!IsEmpty(q))
        printf("Queue underflow\n");
    else
        q->Front = Decrement(q->Front, q);
}

ElementType FrontAndDequeue(Queue q)
{
    if (!IsEmpty(q))
    {
        q->Front = Decrement(q->Front, q);
        return q->Array[increment(q->Front)];
    }
    printf("Empty Queue\n");
    return 0;
}