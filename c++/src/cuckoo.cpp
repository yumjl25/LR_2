#include <iostream>
#include "cuckoo.h"

using namespace std;

static unsigned int hash1(const string& key, int cap) {
    unsigned int h = 0;
    for (char c : key) h = (h * 31 + c) % cap;
    return h;
}

static unsigned int hash2(const string& key, int cap) {
    unsigned int h = 5381;
    for (char c : key) h = ((h << 5) + h) + c;
    return h % cap;
}

void cuckooInit(CuckooTable* ct, int capacity) {
    ct->capacity = capacity;
    ct->size = 0;
    ct->table1 = new CuckooEntry[capacity];
    ct->table2 = new CuckooEntry[capacity];
    for (int i = 0; i < capacity; i++) {
        ct->table1[i].isOccupied = false;
        ct->table2[i].isOccupied = false;
    }
}

void cuckooFree(CuckooTable* ct) {
    delete[] ct->table1;
    delete[] ct->table2;
    ct->table1 = nullptr;
    ct->table2 = nullptr;
    ct->size = 0;
    ct->capacity = 0;
}

static bool cuckooInsertHelper(CuckooTable* ct, const string& key, const string& value, int kickLimit) {
    string curKey = key;
    string curVal = value;
    
    bool useTable1 = true;
    
    for (int i = 0; i < kickLimit; i++) {
        if (useTable1) {
            int idx = hash1(curKey, ct->capacity);
            if (!ct->table1[idx].isOccupied) {
                ct->table1[idx] = {curKey, curVal, true};
                return true;
            } else {
                string kickedKey = ct->table1[idx].key;
                string kickedVal = ct->table1[idx].value;
                ct->table1[idx] = {curKey, curVal, true};
                
                curKey = kickedKey;
                curVal = kickedVal;
                useTable1 = false;
            }
        } else {
            int idx = hash2(curKey, ct->capacity);
            if (!ct->table2[idx].isOccupied) {
                ct->table2[idx] = {curKey, curVal, true};
                return true;
            } else {
                string kickedKey = ct->table2[idx].key;
                string kickedVal = ct->table2[idx].value;
                ct->table2[idx] = {curKey, curVal, true};
                
                curKey = kickedKey;
                curVal = kickedVal;
                useTable1 = true;
            }
        }
    }
    return false;
}

bool cuckooAdd(CuckooTable* ct, const string& key, const string& value) {
    string dummy;
    if (cuckooGet(ct, key, dummy)) {
        cuckooDel(ct, key);
    }

    if (cuckooInsertHelper(ct, key, value, 50)) {
        ct->size++;
        return true;
    }
    
    CuckooTable old = *ct;
    cuckooInit(ct, old.capacity * 2);
    
    bool ok = true;
    for (int i = 0; i < old.capacity; i++) {
        if (old.table1[i].isOccupied) {
            if (!cuckooInsertHelper(ct, old.table1[i].key, old.table1[i].value, 50)) ok = false;
        }
        if (old.table2[i].isOccupied) {
            if (!cuckooInsertHelper(ct, old.table2[i].key, old.table2[i].value, 50)) ok = false;
        }
    }
    if (!ok) {
        return cuckooAdd(ct, key, value);
    }
    
    bool res = cuckooInsertHelper(ct, key, value, 50);
    if (res) ct->size++;
    
    cuckooFree(&old);
    return res;
}

bool cuckooGet(CuckooTable* ct, const string& key, string& outValue) {
    int idx1 = hash1(key, ct->capacity);
    if (ct->table1[idx1].isOccupied && ct->table1[idx1].key == key) {
        outValue = ct->table1[idx1].value;
        return true;
    }
    int idx2 = hash2(key, ct->capacity);
    if (ct->table2[idx2].isOccupied && ct->table2[idx2].key == key) {
        outValue = ct->table2[idx2].value;
        return true;
    }
    return false;
}

bool cuckooDel(CuckooTable* ct, const string& key) {
    int idx1 = hash1(key, ct->capacity);
    if (ct->table1[idx1].isOccupied && ct->table1[idx1].key == key) {
        ct->table1[idx1].isOccupied = false;
        ct->size--;
        return true;
    }
    int idx2 = hash2(key, ct->capacity);
    if (ct->table2[idx2].isOccupied && ct->table2[idx2].key == key) {
        ct->table2[idx2].isOccupied = false;
        ct->size--;
        return true;
    }
    return false;
}

bool cuckooContains(CuckooTable* ct, const string& key) {
    string dummy;
    return cuckooGet(ct, key, dummy);
}

void cuckooPrint(CuckooTable* ct) {
    cout << "Table 1" << endl;
    for (int i = 0; i < ct->capacity; i++) {
        if (ct->table1[i].isOccupied) {
            cout << "[" << i << "] " << ct->table1[i].key << " : " << ct->table1[i].value << endl;
        }
    }
    cout << "Table 2" << endl;
    for (int i = 0; i < ct->capacity; i++) {
        if (ct->table2[i].isOccupied) {
            cout << "[" << i << "] " << ct->table2[i].key << " : " << ct->table2[i].value << endl;
        }
    }
}