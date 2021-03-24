#ifndef _HASHTABLE_H
#define _HASHTABLE_H

typedef double ElementType;

struct ListNode;
typedef struct ListNode *Position;
struct HashTableBase;
typedef struct HashTableBase *HashTable;

HashTable InitializeTable(int TableSize);
void DestroyTable(HashTable h);
Position Find(ElementType elem, HashTable h);
ElementType Retrieve(Position pos);
void Insert(ElementType elem, HashTable h);
int NextPrime(int number);

#endif /* _HASHTABLE_H */