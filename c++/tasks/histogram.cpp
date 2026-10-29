#include <iostream>
#include <string>
#include <array.h>

using namespace std;

int main(){
    cout << "Введите текст на английском: ";
    string text;
    getline(cin, text);

    Array uniqueChars;
    arrayInit(&uniqueChars);
    int freq[256] = {0};
    int maxFreq = 0;

    for (char c : text){
        if (c == ' ' || c == '\n' || c == '\r') continue;
        freq[(unsigned char)c]++;
        if (freq[(unsigned char)c] > maxFreq){
            maxFreq = freq[(unsigned char)c];
        }
    }

    for (int i = 0; i < 256; i++){
        if (freq[i] > 0){
            string s(1, (char)i);
            arrayPush(&uniqueChars, s);
        }
    }

    for (int i = 0; i < uniqueChars.size - 1; i++) {
        for (int j = 0; j < uniqueChars.size - i - 1; j++) {
            if (uniqueChars.data[j][0] > uniqueChars.data[j + 1][0]) {
                string temp = uniqueChars.data[j];
                uniqueChars.data[j] = uniqueChars.data[j + 1];
                uniqueChars.data[j + 1] = temp;
            }
        }
    }

    for (int level = maxFreq; level >= 1; level--){
        for (int i = 0; i < uniqueChars.size; i++){
            char c = uniqueChars.data[i][0];
            if (freq[(unsigned char)c] >= level){
                cout << "#";
            }else{
                cout << " ";
            }
        }
        cout << endl;
    }

    for (int i = 0; i < uniqueChars.size; i++){
        cout << uniqueChars.data[i];
    }
    cout << endl;

    arrayFree(&uniqueChars);
    return 0;
}