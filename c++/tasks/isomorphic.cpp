#include <iostream>
#include <string>
#include "cuckoo.h"

using namespace std;

bool isIsomorphic(const string& s, const string& t){
    if (s.length() != t.length()){
        return false;
    }
    CuckooTable mapST;
    CuckooTable mapTS;

    cuckooInit(&mapST, 256);
    cuckooInit(&mapTS, 256);

    for (size_t i = 0; i < s.length(); i++){
        string c1(1, s[i]);
        string c2(1, t[i]);

        string val1, val2;

        bool has1 = cuckooGet(&mapST, c1, val1);
        if (has1 && val1 != c2){
            cuckooFree(&mapST);
            cuckooFree(&mapTS);
            return false;
        }

        bool has2 = cuckooGet(&mapTS, c2, val2);
        if (has2 && val2 != c1){
            cuckooFree(&mapST);
            cuckooFree(&mapTS);
            return false;
        }
        if (!has1){
            cuckooAdd(&mapST, c1, c2);
        }
        if (!has2){
            cuckooAdd(&mapTS, c2, c1);
        }
    }
    cuckooFree(&mapST);
    cuckooFree(&mapTS);
    return true;
}

int main(){
    cout <<"Изоморфные строки" << endl;

    string s, t;

    cout << "Введите первую строку: ";
    cin >> s;
    cout << "Введите вторую строку: ";
    cin >> t;

    if (isIsomorphic(s, t)) {
        cout << "Результат: Строки изоморфны (TRUE)" << endl;
    } else {
        cout << "Результат: Строки не изоморфны (FALSE)" << endl;
    }

    return 0;
}



