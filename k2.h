#ifndef _k2_h_
#define _k2_h_

#include "k1.h"
#include <map>
#include <vector>
#include <string>

using namespace std;

struct SimbolosK2 {
 char simbolo;
 int frequencia;
};

struct ContextoK2{
    SimbolosK2 simbolos[28];
    int simbolosNuncaVistos;
    string contextoAnterior;
};

class K2{
    private:
        map<string, ContextoK2> contextos;
        int totalSimbolosLidos;
        K1 contextoK1;
        K0 contextoK0;
        ContextoMenos1 contextoMenos1;

    public:
        K2();
        void adicionarSimbolo(const string& contexto, char simbolo);
        void ordenarSimbolos(ContextoK2& contexto);
        int posicaoSimbolo(const ContextoK2& contexto, char simbolo);
        string chamarRO(const string& contexto, char simboloNuncaVisto);
        vector<int> getFrequencias(const ContextoK2& contexto);
        void adicionarFrequencia(ContextoK2& contexto, int posicao);
        string arvoreCodigoSimbolo(ContextoK2& contexto, int posicao);
        string gerarCodigo(const string& contextoAnterior, string palavra);
};



#endif