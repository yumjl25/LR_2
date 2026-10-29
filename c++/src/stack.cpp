#include <iostream>
#include "stack.h"

using namespace std;

void stackInit(Stack* s){
    s->head = nullptr;
}

void stackFree(Stack* s){
    SNode* cur = s->head;
    while(cur != nullptr){
        SNode* next = cur->next;
        delete cur;
        cur = next;
    }
    s->head = nullptr;
}

bool stackIsEmpty(Stack* s){
    return s->head == nullptr;
}

void stackPush(Stack* s, const std::string& value){
    SNode* new_node = new SNode{value, s->head};
    s->head = new_node;
}

bool stackPop(Stack* s, std::string& out){
    if (stackIsEmpty(s)){
        cout << "Stack is empty" << endl;
        return false;
    }
    SNode* del_node = s->head;
    out = del_node->data;
    s->head = del_node->next;
    delete del_node;
    return true;
}

bool stackGet(Stack* s, std::string& out){
    if (stackIsEmpty(s)){
        cout << "Stack is empty" << endl;
        return false;
    }
    out = s->head->data;
    return true;
}

void stackPrint(Stack* s){
    if (stackIsEmpty(s)){
        cout << "Stack is empty" << endl;
        return;
    }
    SNode* cur = s->head;
    while(cur != nullptr){
        cout << cur->data << endl;
        cur = cur->next;
    }
}