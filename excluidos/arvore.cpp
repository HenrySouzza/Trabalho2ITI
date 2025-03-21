#include <iostream>
#include <string>
#include "arvore.h"
#include <vector>
#include <algorithm>

using namespace std;

No::No(int valor) {
    this->valor = valor;
    this->anterior = nullptr;
    this->noEscolhido = false;
    this->ADD1 = true;
}

void copiarNo(No *no, const No &copiado) {
    no->valor = copiado.valor;
    no->anterior = copiado.anterior;
    no->ADD1 = copiado.ADD1;
    no->noEscolhido = copiado.noEscolhido;
}

void copiarPonteiroNo(No *copiado, No &no) {
    no.valor = copiado->valor;
    no.anterior = copiado->anterior;
    no.ADD1 = copiado->ADD1;
    no.noEscolhido = copiado->noEscolhido;
}

bool compararNos(const No &a, const No &b) {
    return a.valor > b.valor;  // Ordenação decrescente
}

string Arvore::criarArvore(int *vetor, int tamanho, int posicao) {
    if (tamanho <= 0) return "";

    // Criando o vetor de nós
    vector<No> raizes(tamanho);
    for (int i = 0; i < tamanho; ++i) {
        raizes[i].valor = vetor[i];
    }

    raizes[posicao].noEscolhido = true;
    int aux = tamanho;

    while (aux > 1) {
        // Criando um novo nó soma
        No *somaNo = new No;
        somaNo->valor = raizes[aux - 1].valor + raizes[aux - 2].valor;

        if (raizes[aux - 1].noEscolhido || raizes[aux - 2].noEscolhido) {
            somaNo->noEscolhido = true;
            No *noAnterior = new No;
            if (raizes[aux - 1].noEscolhido) {
                somaNo->ADD1 = false;
                copiarNo(noAnterior, raizes[aux - 1]);
            } else {
                copiarNo(noAnterior, raizes[aux - 2]);
            }
            somaNo->anterior = noAnterior;
        }

        // Substituir um dos nós pelo novo nó soma
        copiarPonteiroNo(somaNo, raizes[aux - 2]);

        // Liberar memória do nó soma
        delete somaNo;

        // Ordenar os nós novamente
        sort(raizes.begin(), raizes.end() - (tamanho - aux + 1), compararNos);
        aux--;
    }

    // Gerando o código binário
    string palavraCodigo = "";
    No *auxiliar = new No;
    copiarNo(auxiliar, raizes[0]);

    while (auxiliar->anterior != nullptr) {
        No *auxiliarRemover = new No;
        if(auxiliar->ADD1 == true){
            palavraCodigo += "1" ;
        }else{
            palavraCodigo += "0";
        }
        auxiliarRemover = auxiliar;
        auxiliar = auxiliar->anterior;
        delete auxiliarRemover;
    }
    delete auxiliar;

    return palavraCodigo;
}
