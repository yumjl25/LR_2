#ifndef LIST_H
#define LIST_H
#include <string>

struct LNode {
    std::string data;
    LNode* prev;
    LNode* next;
};

struct List {
    LNode* head;
    LNode* tail;
    int size;
};

void listInit(List* list);
void listFree(List* list);
bool listIsEmpty(List* list);

void listPushHead(List* list, const std::string& value);
void listPushTail(List* list, const std::string& value);
void listPushBefore(List* list, const std::string& target, const std::string& value);
void listPushAfter(List* list, const std::string& target, const std::string& value);

bool listDelHead(List* list, std::string& out);
bool listDelTail(List* list, std::string& out);
bool listDelBefore(List* list, const std::string& target, std::string& out);
bool listDelAfter(List* list, const std::string& target, std::string& out);
bool listDelValue(List* list, const std::string& value);
bool listDelByKey(List* list, const std::string& key);

bool listSearch(List* list, const std::string& value);

bool listGetHead(List* list, std::string& out);
bool listGetTail(List* list, std::string& out);
bool listGetAt(List* list, int index, std::string& out);

void listPrint(List* list);

#endif