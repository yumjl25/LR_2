#include <iostream>
#include "array.h"

using namespace std;

static const int ARRAY_INIT_CAPACITY = 4;

void arrayInit(Array* a) {
    a->data = new std::string[ARRAY_INIT_CAPACITY];
    a->size = 0;
    a->capacity = ARRAY_INIT_CAPACITY;
}

void arrayFree(Array* a) {
    delete[] a->data;
    a->data = nullptr;
    a->size = 0;
    a->capacity = 0;
}

bool arrayIsEmpty(Array* a) {
    return a->size == 0;
}

int arrayLen(Array* a) {
    return a->size;
}

static void arrayResize(Array* a) {
    int new_capacity = a->capacity * 2;
    std::string* new_data = new std::string[new_capacity];
    for (int i = 0; i < a->size; i++) {
        new_data[i] = a->data[i];
    }
    delete[] a->data;
    a->data = new_data;
    a->capacity = new_capacity;
}

void arrayPush(Array* a, const std::string& v) {
    if (a->size == a->capacity) {
        arrayResize(a);
    }
    a->data[a->size] = v;
    a->size++;
}

void arrayPushAt(Array* a, const std::string& v, int index) {
    if (index < 0 || index > a->size) {
        cout << "Index out of range" << endl;
        return;
    }
    if (a->size == a->capacity) {
        arrayResize(a);
    }
    for (int i = a->size; i > index; i--) {
        a->data[i] = a->data[i - 1];
    }
    a->data[index] = v;
    a->size++;
}

bool arrayGet(Array* a, int index, std::string& out) {
    if (index < 0 || index >= a->size) {
        cout << "Index out of range" << endl;
        return false;
    }
    out = a->data[index];
    return true;
}

void arraySet(Array* a, int index, const std::string& v) {
    if (index < 0 || index >= a->size) {
        cout << "Index out of range" << endl;
        return;
    }
    a->data[index] = v;
}

bool arrayDel(Array* a, int index, std::string& out) {
    if (index < 0 || index >= a->size) {
        cout << "Index out of range" << endl;
        return false;
    }
    out = a->data[index];
    for (int i = index; i < a->size - 1; i++) {
        a->data[i] = a->data[i + 1];
    }
    a->size--;
    return true;
}

void arrayPrint(Array* a) {
    if (arrayIsEmpty(a)) {
        cout << "ARRAY: empty" << endl;
        return;
    }
    cout << "ARRAY:" << endl;
    for (int i = 0; i < a->size; i++) {
        cout << "  [" << i << "] " << a->data[i] << endl;
    }
}