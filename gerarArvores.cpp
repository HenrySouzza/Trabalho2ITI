#include "gerarArvores.h"


// Função para criar a árvore de Huffman
HuffmanNode* criarArvoreHuffman(const vector<double>& valores) {
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare> fila;
    
    // Criar nós iniciais com índice único para cada elemento
    for (size_t i = 0; i < valores.size(); i++) {
        fila.push(new HuffmanNode(valores[i], i));
    }
    
    // Construção da árvore
    while (fila.size() > 1) {
        HuffmanNode* esq = fila.top(); fila.pop();
        HuffmanNode* dir = fila.top(); fila.pop();
        
        HuffmanNode* novoNo = new HuffmanNode(esq->valor + dir->valor);
        novoNo->esq = esq;
        novoNo->dir = dir;
        
        fila.push(novoNo);
    }
    
    return fila.top(); // Retorna a raiz da árvore
}

// Função para Gerar os Códigos de Huffman
void gerarCodigos(HuffmanNode* raiz, map<double, string>& codigos, string codigo) {
    if (!raiz) return;
    
    // Se for uma folha, armazena o índice e seu código
    if (!raiz->esq && !raiz->dir) {
        codigos[raiz->indice] = codigo;
    }
    
    gerarCodigos(raiz->esq, codigos, codigo + "0");
    gerarCodigos(raiz->dir, codigos, codigo + "1");
}

// Função para obter o código de Huffman de um elemento na posição desejada
string obterCodigoHuffman(vector<double>& valores, int posicao) {

        
    sort(valores.begin(), valores.end(), [](double a, double b) {
        return a > b;
    });
    
    if (posicao < 0 || posicao >= valores.size()) {
        return "";
    }
    
    HuffmanNode* raiz = criarArvoreHuffman(valores);
    
    // Gerar mapa de códigos
    map<double, string> codigos;
    gerarCodigos(raiz, codigos, "");
    
    return codigos[posicao];
}

