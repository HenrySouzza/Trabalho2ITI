#ifndef _gerarArvores_H
#define _gerarArvores_H

#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include <cmath>

using namespace std;

// Estrutura do nó da árvore de Huffman
struct HuffmanNode {
    double valor;
    int indice;
    HuffmanNode *esq, *dir;
    
    HuffmanNode(double valor, int indice = -1) : valor(valor), indice(indice), esq(nullptr), dir(nullptr) {}
};

// Comparador para a fila de prioridade
struct Compare {
    bool operator()(HuffmanNode* a, HuffmanNode* b) {
        return a->valor > b->valor;
    }
};

// Função para criar a árvore de Huffman
HuffmanNode* criarArvoreHuffman(const vector<double>& valores);
// Função para Gerar os Códigos de Huffman
void gerarCodigos(HuffmanNode* raiz, map<int, string>& codigos, string codigo = "");
// Função para obter o código de Huffman de um elemento na posição desejada
string obterCodigoHuffman(vector<double>& valores, int posicao);

#endif