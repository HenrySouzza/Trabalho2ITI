#include "filtrar_arquivo.h"
#include "k_1.h"
#include <iostream>
#include "arvore.h"

using namespace std;

int main() {

    ifstream arquivo("MemoriasPostumas.txt");
    if (!arquivo) {
        cerr << "Erro ao abrir o arquivo de entrada!" << endl;
        return 1;
    }
    ofstream arquivo_saida("saida.txt");
    if (!arquivo_saida) {
        cerr << "Erro ao abrir o arquivo de saída!" << endl;
        return 1;
    }
    limpar_texto(arquivo, arquivo_saida);

    
    int vetor[] = {60, 31, 16, 8, 4, 4};
    int tamanho = sizeof(vetor) / sizeof(vetor[0]);
    int posicao = 0;

    Arvore arvore;
    string codigo = arvore.criarArvore(vetor, tamanho, posicao);

    cout << "Codigo gerado pela arvore: " << codigo << endl;

    return 0;
}
