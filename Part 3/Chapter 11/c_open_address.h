#ifndef OPEN_ADDRESS_H
#define OPEN_ADDRESS_H

typedef double ElementType;

typedef unsigned int Index;
typedef Index Position;

struct HashTableBase;
typedef struct HashTableBase *HashTable;

HashTable InitializeTable(int TableSize);
void DestroyTable(HashTable h);
Position Find(ElementType elem, HashTable h);
void Insert(ElementType elem, HashTable h);
ElementType Retrieve(Position pos, HashTable h);
HashTable Rehash(HashTable h);
int NextPrime(int number);

#endif // OPEN_ADDRESS_H