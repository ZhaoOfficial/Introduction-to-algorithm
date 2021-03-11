#ifndef _QUEUE_H
#define _QUEUE_H

typedef double ElementType;

struct QueueRecord;
typedef struct QueueRecord* Queue;

int IsEmpty(Queue q);
int IsFull(Queue q);
Queue CreateQueue(int MaxElements);
void DisposeQueue(Queue q);
void MakeEmpty(Queue q);
void Enqueue(ElementType elem, Queue q);
ElementType Front(Queue q);
void Dequeue(Queue q);
ElementType FrontAndDequeue(Queue q);

#endif /* _QUEUE_H */