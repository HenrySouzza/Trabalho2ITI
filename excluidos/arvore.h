#ifndef _ARVORE_H
#define _ARVORE_H

#include <iostream>
#include <string>

using namespace std;

struct No {
    int valor;
    No *anterior;
    bool ADD1;
    bool noEscolhido;

    No(int valor = 0);
};

// Funções para copiar os nós
void copiarNo(No *no, const No &copiado);
void copiarPonteiroNo(No *copiado, No &no);

class Arvore {
public:
    string criarArvore(int *vetor, int tamanho, int posicao);
};

#endif
