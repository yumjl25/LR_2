#ifndef STACK_H
#define STACK_H

#include <string>

struct SNode {
    std::string data;
    SNode* next;
};

struct Stack {
    SNode* head;
};

void stackInit(Stack* s);
void stackFree(Stack* s);
bool stackIsEmpty(Stack* s);

void stackPush(Stack* s, const std::string& value);
bool stackPop(Stack* s, std::string& out);
bool stackGet(Stack* s, std::string& out);
void stackPrint(Stack* s);
#endif