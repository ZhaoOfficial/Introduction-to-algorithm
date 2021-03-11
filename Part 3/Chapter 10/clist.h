#ifndef _List_H
#define _List_H

typedef double ElementType;

struct Node;
typedef struct Node* PtrToNode;
typedef PtrToNode Position;
typedef PtrToNode List;


void MakeEmpty(List list);
int IsEmpty(List list);
int IsLast(Position pos, List list);
Position Find(ElementType elem, List list);
void Delete(ElementType elem, List list);
Position FindPrevious(ElementType elem, List list);
void Insert(ElementType elem, List list, Position pos);
void DeleteList(List list);
Position Header(List list);
Position First(List list);
ElementType Retrieve(Position pos);


#endif /* _LIST_H */