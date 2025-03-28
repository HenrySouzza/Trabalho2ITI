#ifndef _k1_h_
#define _k1_h_

#include "k0.h"
#include "gerarArvores.h"
#include "leitor.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

struct SimbolosK1 {
    char simbolo;
    int frequencia;

    SimbolosK1() {
        this->frequencia = 0;
    }
};

struct ContextoK1 {
    SimbolosK1 simbolos[28];
    int simbolosNuncaVistos;
    char contextoAnterior;

    ContextoK1() : simbolosNuncaVistos(27), contextoAnterior('\0') {}
};

class K1 {
private:
    map<char, ContextoK1> contextos;
    int totalSimbolosLidos;
    K0 contextoK0; // Usado quando o contexto não existe ainda
    ContextoMenos1 contextoMenos1;

public:
    K1();
    void adicionarSimbolo(char contexto, char simbolo);
    void ordenarSimbolos(ContextoK1& contexto);
    int posicaoSimbolo(const ContextoK1& contexto, char simbolo);
    string chamarRO(char contexto, char simboloNuncaVisto);
    vector<int> getFrequencias(const ContextoK1& contexto);
    void adicionarFrequencia(ContextoK1& contexto, int posicao);
    string arvoreCodigoSimbolo(ContextoK1& contexto, int posicao);
    string gerarCodigo(char contextoAnterior, string palavra);
};

#endif