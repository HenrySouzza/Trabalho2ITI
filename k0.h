#ifndef _k0_h_
#define _k0_h_

#include"k_1.h"
#include"gerarArvores.h"
#include"leitor.h"

#include<iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct SimbolosK0
{
    char simbolo;
    int frequencia;

    SimbolosK0()
    {
        this->frequencia = 0;
    }
};

class K0{
private:

    SimbolosK0 simbolo[28];
    int simbolosNuncaVistos;
    int totalSimbolosLidos;
    ContextoMenos1 contextoMenos1;
public:
    K0();
    void adicionarSimbolo(char simbolo);
    void ordenarSimbolos();
    int posicaoSimbolo(char simbolo);
    string chamarRO(char simboloNuncaVisto);
    vector<int> getFrequencias();
    void adicionarFrequencia(int posicao);
    string arvoreCodigoSimbolo(int posicao);
    string gerarCodigo(string palavra);
    int getPrimeiraPosicaoVazia();
};

#endif