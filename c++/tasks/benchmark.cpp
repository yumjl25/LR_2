#include <iostream>
#include <string>
#include <chrono>
#include <cstdlib> 
#include "hash.h"
#include "cuckoo.h"

using namespace std;
using namespace std::chrono;

string randomString(int length) {
    string s = "";
    for (int i = 0; i < length; i++) {
        s += (char)('a' + rand() % 26);
    }
    return s;
}

int main() {
    const int N = 5000;
    const int CAPACITY = 20000;

    cout << "Эмпирический анализ хеш-таблиц" << endl;
    cout << "Количество элементов: " << N << endl;

    string* keys = new string[N];
    for (int i = 0; i < N; i++) {
        keys[i] = randomString(5 + rand() % 5);
    }

    HashTable ht;
    hashInit(&ht, CAPACITY);

    auto start_chaining = high_resolution_clock::now();
    for (int i = 0; i < N; i++) {
        hashAdd(&ht, keys[i], "val");
    }
    auto end_chaining = high_resolution_clock::now();
    duration<double, milli> time_chaining = end_chaining - start_chaining;

    cout << "\n[Метод цепочек]" << endl;
    cout << "Время вставки: " << time_chaining.count() << " мс" << endl;
    cout << "Занято бакетов: " << ht.size << endl;


    CuckooTable ct;
    cuckooInit(&ct, CAPACITY);

    auto start_cuckoo = high_resolution_clock::now();
    for (int i = 0; i < N; i++) {
        cuckooAdd(&ct, keys[i], "val");
    }
    auto end_cuckoo = high_resolution_clock::now();
    duration<double, milli> time_cuckoo = end_cuckoo - start_cuckoo;

    cout << "\n[Хеширование кукушки]" << endl;
    cout << "Время вставки: " << time_cuckoo.count() << " мс" << endl;
    cout << "Занято ячеек: " << ct.size << endl;

    auto start_search_chain = high_resolution_clock::now();
    for (int i = 0; i < 100; i++) {
        string dummy;
        hashGet(&ht, keys[rand() % N], dummy);
    }
    auto end_search_chain = high_resolution_clock::now();
    
    auto start_search_cuckoo = high_resolution_clock::now();
    for (int i = 0; i < 100; i++) {
        string dummy;
        cuckooGet(&ct, keys[rand() % N], dummy);
    }
    auto end_search_cuckoo = high_resolution_clock::now();

    cout << "\n[Поиск 100 элементов]" << endl;
    cout << "Цепочки: " << duration<double, milli>(end_search_chain - start_search_chain).count() << " мс" << endl;
    cout << "Кукушка: " << duration<double, milli>(end_search_cuckoo - start_search_cuckoo).count() << " мс" << endl;

    hashFree(&ht);
    cuckooFree(&ct);
    delete[] keys;

    return 0;
}