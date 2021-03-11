#ifndef _STACK_H
#define _STACK_H

typedef double ElementType;

struct Node;
typedef struct Node* PtrToNode;
typedef PtrToNode Stack;

int IsEmpty(Stack s);
Stack CreateStack(void);
void DisposeStack(Stack s);
void MakeEmpty(Stack s);
void Push(ElementType elem, Stack s);
ElementType Top(Stack s);
void Pop(Stack s);

#endif /* _STACK_H */