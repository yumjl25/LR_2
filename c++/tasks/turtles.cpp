#include <iostream>
#include <string>
#include "hash.h"

using namespace std;

int main(){
    int N;
    cout << "Введите количество черепах N: ";
    cin >> N;

    HashTable ht;
    hashInit(&ht, 1000);

    int max_true = 0;
    for (int i = 0; i < N; i++){
        int a, b;
        cin >> a >> b;
        if (a + b == N - 1){
            string key = to_string(a) + "_" + to_string(b);
            if (!hashContains(&ht, key)){
                hashAdd(&ht, key, "1");
                max_true++;
            }
        }
    }
    cout << "Максимальное количество правдивых черепах: " << max_true << endl;
    hashFree(&ht);
    return 0;
}