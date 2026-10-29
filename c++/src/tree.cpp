#include <iostream>
#include "tree.h"

using namespace std;

void treeInit(HuffmanTree* tree) {
    tree->root = nullptr;
}

void treeFree(TNode* node) {
    if (node == nullptr) return;
    treeFree(node->left);
    treeFree(node->right);
    delete node;
}

TNode* treeCreateNode(char ch, int weight) {
    TNode* node = new TNode;
    node->ch = ch;
    node->weight = weight;
    node->left = nullptr;
    node->right = nullptr;
    return node;
}

void treePrintInorder(TNode* root) {
    if (root == nullptr) return;
    treePrintInorder(root->left);
    cout << "[" << root->ch << ":" << root->weight << "] ";
    treePrintInorder(root->right);
}

void treePrintPreorder(TNode* root) {
    if (root == nullptr) return;
    cout << "[" << root->ch << ":" << root->weight << "] ";
    treePrintPreorder(root->left);
    treePrintPreorder(root->right);
}

void treePrintPostorder(TNode* root) {
    if (root == nullptr) return;
    treePrintPostorder(root->left);
    treePrintPostorder(root->right);
    cout << "[" << root->ch << ":" << root->weight << "] ";
}