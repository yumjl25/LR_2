#include <iostream>
#include "list.h"

using namespace std;

void listInit(List* list) {
    list->head = nullptr;
    list->tail = nullptr;
    list->size = 0;
}

void listFree(List* list) {
    LNode* cur = list->head;
    while (cur != nullptr) {
        LNode* next = cur->next;
        delete cur;
        cur = next;
    }
    list->head = nullptr;
    list->tail = nullptr;
    list->size = 0;
}

bool listIsEmpty(List* list) {
    return list->head == nullptr;
}

void listPushHead(List* list, const std::string& value) {
    LNode* node = new LNode{value, nullptr, list->head};
    if (list->head != nullptr) {
        list->head->prev = node;
    } else {
        list->tail = node;
    }
    list->head = node;
    list->size++;
}

void listPushTail(List* list, const std::string& value) {
    LNode* node = new LNode{value, list->tail, nullptr};
    if (list->tail != nullptr) {
        list->tail->next = node;
    } else {
        list->head = node;
    }
    list->tail = node;
    list->size++;
}

void listPushBefore(List* list, const std::string& target, const std::string& value) {
    LNode* cur = list->head;
    while (cur != nullptr && cur->data != target) {
        cur = cur->next;
    }
    if (cur == nullptr) {
        cout << "Target not found" << endl;
        return;
    }
    if (cur == list->head) {
        listPushHead(list, value);
        return;
    }
    LNode* node = new LNode{value, cur->prev, cur};
    cur->prev->next = node;
    cur->prev = node;
    list->size++;
}

void listPushAfter(List* list, const std::string& target, const std::string& value) {
    LNode* cur = list->head;
    while (cur != nullptr && cur->data != target) {
        cur = cur->next;
    }
    if (cur == nullptr) {
        cout << "Target not found" << endl;
        return;
    }
    if (cur == list->tail) {
        listPushTail(list, value);
        return;
    }
    LNode* node = new LNode{value, cur, cur->next};
    cur->next->prev = node;
    cur->next = node;
    list->size++;
}

bool listDelHead(List* list, std::string& out) {
    if (listIsEmpty(list)) {
        cout << "List is empty" << endl;
        return false;
    }
    LNode* old = list->head;
    out = old->data;
    list->head = old->next;
    if (list->head != nullptr) {
        list->head->prev = nullptr;
    } else {
        list->tail = nullptr;
    }
    delete old;
    list->size--;
    return true;
}

bool listDelTail(List* list, std::string& out) {
    if (listIsEmpty(list)) {
        cout << "List is empty" << endl;
        return false;
    }
    LNode* old = list->tail;
    out = old->data;
    list->tail = old->prev;
    if (list->tail != nullptr) {
        list->tail->next = nullptr;
    } else {
        list->head = nullptr;
    }
    delete old;
    list->size--;
    return true;
}

bool listDelBefore(List* list, const std::string& target, std::string& out) {
    LNode* cur = list->head;
    while (cur != nullptr && cur->data != target) {
        cur = cur->next;
    }
    if (cur == nullptr || cur->prev == nullptr) {
        cout << "Nothing to delete before" << endl;
        return false;
    }
    LNode* victim = cur->prev;
    out = victim->data;
    cur->prev = victim->prev;
    if (victim->prev != nullptr) {
        victim->prev->next = cur;
    } else {
        list->head = cur;
    }
    delete victim;
    list->size--;
    return true;
}

bool listDelAfter(List* list, const std::string& target, std::string& out) {
    LNode* cur = list->head;
    while (cur != nullptr && cur->data != target) {
        cur = cur->next;
    }
    if (cur == nullptr || cur->next == nullptr) {
        cout << "Nothing to delete after" << endl;
        return false;
    }
    LNode* victim = cur->next;
    out = victim->data;
    cur->next = victim->next;
    if (victim->next != nullptr) {
        victim->next->prev = cur;
    } else {
        list->tail = cur;
    }
    delete victim;
    list->size--;
    return true;
}

bool listDelValue(List* list, const std::string& value) {
    LNode* cur = list->head;
    while (cur != nullptr && cur->data != value) {
        cur = cur->next;
    }
    if (cur == nullptr) return false;

    if (cur->prev != nullptr) {
        cur->prev->next = cur->next;
    } else {
        list->head = cur->next;
    }
    if (cur->next != nullptr) {
        cur->next->prev = cur->prev;
    } else {
        list->tail = cur->prev;
    }
    delete cur;
    list->size--;
    return true;
}

bool listDelByKey(List* list, const std::string& key) {
    if (listIsEmpty(list)) return false;

    std::string prefix = key + ":";
    LNode* cur = list->head;
    
    while (cur != nullptr) {
        if (cur->data.compare(0, prefix.length(), prefix) == 0) {
            if (cur->prev != nullptr) {
                cur->prev->next = cur->next;
            } else {
                list->head = cur->next;
            }
            
            if (cur->next != nullptr) {
                cur->next->prev = cur->prev;
            } else {
                list->tail = cur->prev;
            }
            
            delete cur;
            list->size--;
            return true;
        }
        cur = cur->next;
    }
    return false;
}

bool listSearch(List* list, const std::string& value) {
    LNode* cur = list->head;
    while (cur != nullptr) {
        if (cur->data == value) return true;
        cur = cur->next;
    }
    return false;
}

bool listGetHead(List* list, std::string& out) {
    if (listIsEmpty(list)) {
        cout << "List is empty" << endl;
        return false;
    }
    out = list->head->data;
    return true;
}

bool listGetTail(List* list, std::string& out) {
    if (listIsEmpty(list)) {
        cout << "List is empty" << endl;
        return false;
    }
    out = list->tail->data;
    return true;
}

bool listGetAt(List* list, int index, std::string& out) {
    if (index < 0 || index >= list->size) {
        cout << "Index out of range" << endl;
        return false;
    }
    LNode* cur = list->head;
    for (int i = 0; i < index; i++) {
        cur = cur->next;
    }
    out = cur->data;
    return true;
}

void listPrint(List* list) {
    if (listIsEmpty(list)) {
        cout << "LIST: empty" << endl;
        return;
    }
    cout << "LIST:" << endl;
    LNode* cur = list->head;
    while (cur != nullptr) {
        cout << "  " << cur->data << endl;
        cur = cur->next;
    }
}