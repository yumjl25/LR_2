#include <iostream>
#include <string>
#include "tree.h"

using namespace std;

void generateCodes(TNode* node, string code, string codes[256]) {
    if (node == nullptr) return;
    if (node->left == nullptr && node->right == nullptr) {
        codes[(unsigned char)node->ch] = code;
    }
    generateCodes(node->left, code + "0", codes);
    generateCodes(node->right, code + "1", codes);
}

string decode(TNode* root, const string& encoded) {
    string result = "";
    TNode* cur = root;
    for (char bit : encoded) {
        if (bit == '0') cur = cur->left;
        else cur = cur->right;

        if (cur->left == nullptr && cur->right == nullptr) {
            result += cur->ch;
            cur = root;
        }
    }
    return result;
}

void sortNodes(TNode* nodes[], int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (nodes[j]->weight < nodes[j+1]->weight) {
                TNode* temp = nodes[j];
                nodes[j] = nodes[j+1];
                nodes[j+1] = temp;
            }
        }
    }
}

int main() {
    cout << "Введите строку для сжатия: " << endl;
    string text;
    getline(cin, text);

    if (text.empty()) return 0;

    int freq[256] = {0};
    for (char c : text) {
        freq[(unsigned char)c]++;
    }

    TNode* nodes[256];
    int nodeCount = 0;
    
    for (int i = 0; i < 256; i++) {
        if (freq[i] > 0) {
            nodes[nodeCount] = treeCreateNode((char)i, freq[i]);
            nodeCount++;
        }
    }

    if (nodeCount == 1) {
        char onlyChar = nodes[0]->ch;
        cout << "\nТаблица кодов:" << endl;
        cout << onlyChar << " : 0" << endl;
        
        string encoded = "";
        for (size_t i = 0; i < text.length(); i++) {
            encoded += "0";
        }
        
        cout << "\nЗакодированная строка: " << encoded << endl;
        cout << "Декодированная строка: " << text << endl;
        
        treeFree(nodes[0]);
        return 0; 
    }

    while (nodeCount > 1) {
        sortNodes(nodes, nodeCount);

        TNode* right = nodes[nodeCount - 1];
        nodeCount--;
        TNode* left = nodes[nodeCount - 1];
        nodeCount--;

        TNode* parent = treeCreateNode('\0', left->weight + right->weight);
        parent->left = left;
        parent->right = right;
        
        nodes[nodeCount] = parent;
        nodeCount++;
    }

    TNode* root = nodes[0];

    string codes[256];
    generateCodes(root, "", codes);

    cout << "\nТаблица кодов:" << endl;
    for (int i = 0; i < 256; i++) {
        if (!codes[i].empty()) {
            cout << (char)i << " : " << codes[i] << endl;
        }
    }

    string encoded = "";
    for (char c : text) {
        encoded += codes[(unsigned char)c];
    }
    cout << "\nЗакодированная строка: " << encoded << endl;

    string decoded = decode(root, encoded);
    cout << "Декодированная строка: " << decoded << endl;

    treeFree(root);
    return 0;
}