#ifndef _STACK_H
#define _STACK_H

typedef double ElementType;

struct StackRecord;
typedef struct StackRecord* Stack;

int IsEmpty(Stack s);
int IsFull(Stack s);
Stack CreateStack(int MaxElements);
void DisposeStack(Stack s);
void MakeEmpty(Stack s);
void Push(ElementType elem, Stack s);
ElementType Top(Stack s);
void Pop(Stack s);
ElementType TopAndPop(Stack s);

#endif /* _STACK_H */