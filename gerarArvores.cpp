#include "gerarArvores.h"


using namespace std;

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

// Função para criar a árvore de Huffman
HuffmanNode* criarArvoreHuffman(const vector<int>& valores) {
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
void gerarCodigos(HuffmanNode* raiz, map<int, string>& codigos, string codigo = "") {
    if (!raiz) return;
    
    // Se for uma folha, armazena o índice e seu código
    if (!raiz->esq && !raiz->dir) {
        codigos[raiz->indice] = codigo;
    }
    
    gerarCodigos(raiz->esq, codigos, codigo + "0");
    gerarCodigos(raiz->dir, codigos, codigo + "1");
}

// Função para obter o código de Huffman de um elemento na posição desejada
string obterCodigoHuffman(const vector<int>& valores, int posicao) {
    if (posicao < 0 || posicao >= valores.size()) {
        return "Erro: Posição inválida.";
    }
    
    HuffmanNode* raiz = criarArvoreHuffman(valores);
    
    // Gerar mapa de códigos
    map<int, string> codigos;
    gerarCodigos(raiz, codigos);
    
    return codigos[posicao];
}


