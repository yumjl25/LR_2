#ifndef HUFFMAN_H
#define HUFFMAN_H

struct TNode {
    char ch;
    int weight;
    TNode* left;
    TNode* right;
};

struct HuffmanTree {
    TNode* root;
};

void treeInit(HuffmanTree* tree);
void treeFree(TNode* node);

TNode* treeCreateNode(char ch, int weight);

void treePrintInorder(TNode* root);
void treePrintPreorder(TNode* root);
void treePrintPostorder(TNode* root);

#endif