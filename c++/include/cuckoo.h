#ifndef CUCKOO_H
#define CUCHOO_H

#include <string>

struct CuckooEntry{
    std::string key;
    std::string value;
    bool isOccupied;
};

struct CuckooTable{
    CuckooEntry* table1;
    CuckooEntry* table2;
    int capacity;
    int size;
};

void cuckooInit(CuckooTable* ct, int capacity);
void cuckooFree(CuckooTable* ct);

bool cuckooAdd(CuckooTable* ct, const std::string& key, const std::string& value);
bool cuckooGet(CuckooTable* ct, const std::string& key, std::string& outValue);
bool cuckooDel(CuckooTable* ct, const std::string& key);
bool cuckooContains(CuckooTable* ct, const std::string& key);
void cuckooPrint(CuckooTable* ct);

#endif