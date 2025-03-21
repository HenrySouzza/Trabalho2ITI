#ifndef _gerarArvores_H
#define _gerarArvores_H

#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>

// Estrutura do nó da árvore de Huffman
struct HuffmanNode {
    int valor, indice;
    HuffmanNode *esq, *dir;
    
    HuffmanNode(int valor, int indice = -1) : valor(valor), indice(indice), esq(nullptr), dir(nullptr) {}
};

// Comparador para a fila de prioridade
struct Compare {
    bool operator()(HuffmanNode* a, HuffmanNode* b) {
        return a->valor > b->valor;
    }
};


#endif