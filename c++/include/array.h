#ifndef ARRAY_H
#define ARRAY_H
#include <string>

struct Array {
    std::string* data;
    int size;
    int capacity;
};

void arrayInit(Array* a);
void arrayFree(Array* a);
bool arrayIsEmpty(Array* a);
int arrayLen(Array* a);
void arrayPush(Array* a, const std::string& v);
void arrayPushAt(Array* a, const std::string& v, int index);
bool arrayGet(Array* a, int index, std::string& out);
void arraySet(Array* a, int index, const std::string& v);
bool arrayDel(Array* a, int index, std::string& out);
void arrayPrint(Array* a);

#endif