#ifndef HASH_H
#define HASH_H

#include <string>

struct HashNode {
    std::string key;
    std::string value;
    HashNode* next;
};

struct HashTable {
    HashNode** buckets;
    int capacity;
    int size;
};

void hashInit(HashTable* ht, int capacity);
void hashFree(HashTable* ht);

void hashAdd(HashTable* ht, const std::string& key, const std::string& value);
bool hashGet(HashTable* ht, const std::string& key, std::string& outValue);
bool hashDel(HashTable* ht, const std::string& key);
bool hashContains(HashTable* ht, const std::string& key);
void hashPrint(HashTable* ht);

#endif