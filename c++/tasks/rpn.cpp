#include <iostream>
#include <sstream>
#include <string>
#include "stack.h"

using namespace std;

bool isOperator(char c){
    return c == '+' || c == '-' || c == '*' || c == '/';
}

int main(){
    Stack s;
    stackInit(&s);

    string input;
    cout << "Введите выражение: " << endl;
    getline(cin, input);

    stringstream ss(input);
    string token;

    while (ss >> token){
        if (token.length() == 1 && isOperator(token[0])){
            string str_b, str_a;
            if (!stackPop(&s, str_b) || !stackPop(&s, str_a)) {
                cout << "Ошибка: недостаточно операндов для оператора " << token << endl;
                stackFree(&s);
                return 1;
            }
            int b = stoi(str_b);
            int a = stoi(str_a);
            int result = 0;

            switch (token[0]) {
                case '+': 
                    result = a + b; 
                    break;
                case '-': 
                    result = a - b; 
                    break;
                case '*': 
                    result = a * b; 
                    break;
                case '/': 
                    if (b == 0) {
                        cout << "Ошибка: деление на ноль" << endl;
                        stackFree(&s);
                        return 1;
                    }
                    result = a / b; 
                    break;
            }
            stackPush(&s, to_string(result));
        }else{
            stackPush(&s, token);
        }
    }
    if (s.head != nullptr && s.head->next == nullptr) {
        string result;
        stackPop(&s, result);
        cout << "Результат: " << result << endl;
    } else {
        cout << "Ошибка: некорректное выражение" << endl;
    }

    stackFree(&s);
    return 0;
}