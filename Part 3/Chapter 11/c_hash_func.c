typedef unsigned int Index;

Index Hash1(const char* Key, int TableSize)
{
    Index HashVal = 0;
    while (*Key != '\0')
        HashVal += *Key++;
    
    return HashVal % TableSize;
}

Index Hash2(const char* Key, int TableSize)
{
    return (Key[0] + 27 * Key[1] + 729 * Key[2]) % TableSize;
}

Index Hash3(const char* Key, int TableSize)
{
    Index HashVal = 0;

    while (*Key != '\0')
        HashVal = (HashVal << 5) + *Key++;

    return HashVal % TableSize;
}