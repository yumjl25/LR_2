#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "hash.h"

using namespace std;

struct Set {
    HashTable ht;
};

void setInit(Set* s) {
    hashInit(&s->ht, 100);
}

void setFree(Set* s) {
    hashFree(&s->ht);
}

void setAdd(Set* s, const string& value) {
    hashAdd(&s->ht, value, "1");
}

void setDel(Set* s, const string& value) {
    hashDel(&s->ht, value);
}

bool setAt(Set* s, const string& value) {
    return hashContains(&s->ht, value);
}

void executeQuery(Set* s, const string& query, bool quiet) {
    stringstream ss(query);
    string cmd, name, value;
    ss >> cmd >> name;
    
    if (cmd == "SETADD") {
        ss >> value;
        setAdd(s, value);
        if (!quiet) cout << value << endl;
    } 
    else if (cmd == "SETDEL") {
        ss >> value;
        setDel(s, value);
        if (!quiet) cout << value << endl;
    } 
    else if (cmd == "SET_AT") {
        ss >> value;
        bool res = setAt(s, value);
        if (!quiet) cout << (res ? "TRUE" : "FALSE") << endl;
    }
    else if (cmd == "PRINT") {
        if (!quiet) {
            cout << "SET " << name << ":" << endl;
            hashPrint(&s->ht);
        }
    }
    else {
        if (!quiet) cout << "Unknown command: " << cmd << endl;
    }
}

void loadFromFile(Set* s, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) return;
    
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        executeQuery(s, line, true);
    }
    file.close();
}

void saveToFile(Set* s, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) return;
    
    for (int i = 0; i < s->ht.capacity; i++) {
        HashNode* cur = s->ht.buckets[i];
        while (cur != nullptr) {
            file << "SETADD myset " << cur->key << "\n";
            cur = cur->next;
        }
    }
    file.close();
}

int main(int argc, char** argv) {
    string filename = "";
    string query = "";

    for (int i = 1; i < argc; i++) {
        string arg = argv[i];
        if (arg == "--file" && i + 1 < argc) {
            filename = argv[++i];
        } else if (arg == "--query" && i + 1 < argc) {
            query = argv[++i];
        }
    }

    if (filename.empty() || query.empty()) {
        cout << "Usage: " << argv[0] << " --file <file> --query '<command>'" << endl;
        return 1;
    }

    Set s;
    setInit(&s);

    loadFromFile(&s, filename);
    
    executeQuery(&s, query, false);
    
    saveToFile(&s, filename);

    setFree(&s);
    return 0;
}