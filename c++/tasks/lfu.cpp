#include <iostream>
#include <string>
#include "hash.h"
#include "list.h"

using namespace std;

int main() {
    int capacity, Q;
    cout << "Введите емкость кэша (cap) и количество запросов (Q): ";
    if (!(cin >> capacity >> Q)) return 0;

    List cache;
    listInit(&cache);

    HashTable map;
    hashInit(&map, 100);
    string output = "";

    for (int i = 0; i < Q; i++) {
        string cmd;
        cin >> cmd;

        if (cmd == "SET") {
            string key, value;
            cin >> key >> value;

            string dummy;
            if (hashGet(&map, key, dummy)) {
                listDelByKey(&cache, key);
            } 
            else if (cache.size >= capacity) {
                string oldest;
                if (listDelHead(&cache, oldest)) {
                    string oldKey = oldest.substr(0, oldest.find(':'));
                    hashDel(&map, oldKey);
                }
            }

            string entry = key + ":" + value + ":1";
            listPushTail(&cache, entry);
            hashAdd(&map, key, entry);

        } else if (cmd == "GET") {
            string key;
            cin >> key;

            string entry;
            if (hashGet(&map, key, entry)) {
                size_t pos1 = entry.find(':');
                size_t pos2 = entry.find(':', pos1 + 1);
                
                string k = entry.substr(0, pos1);
                string v = entry.substr(pos1 + 1, pos2 - pos1 - 1);
                int freq = stoi(entry.substr(pos2 + 1));

                output += v + " ";
                listDelByKey(&cache, k);
                
                string newEntry = k + ":" + v + ":" + to_string(freq + 1);
                listPushTail(&cache, newEntry);
                hashAdd(&map, k, newEntry);
                
            } else {
                output += "-1 ";
            }
        }
    }
    cout << endl;

    listFree(&cache);
    hashFree(&map);
    cout << "Вывод: " << output << endl;
    return 0;
}