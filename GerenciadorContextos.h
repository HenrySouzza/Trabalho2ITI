#ifndef GERENCIADOR_CONTEXTOS_H
#define GERENCIADOR_CONTEXTOS_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <utility>
#include <chrono>


#include "gerarArvores.h"
#include "leitor.h"
#include "k_1.h"
#include "conversor.h"

using namespace std;

struct Simbolo {
    char representacao;
    double frequencia;
    
    bool operator<(const Simbolo& outro) const {
        return frequencia > outro.frequencia;
    }
};

class GerenciadorContextos {
public:

    GerenciadorContextos();

    Simbolo simbolosK0[28];
    unordered_map<string, vector<Simbolo>> tabelaContextosK1;
    unordered_map<string, vector<Simbolo>> tabelaContextosK2;
    unordered_map<string, vector<Simbolo>> tabelaContextosK3;
    unordered_map<string, vector<Simbolo>> tabelaContextosK4;
    unordered_map<string, vector<Simbolo>> tabelaContextosK5;

    string simbolosParaExclusao;
    ContextoMenos1 contextoMenos1;
    //vector<Simbolo> simbolosK0;  // Tamanho fixo 28
    int proximaPosicaoLivre;     // Controla inserções
    // int simbolosNuncaVistos = 27;

    // //K0

      // Métodos para K0
      bool adicionarSimboloK0(char simbolo);
      bool incrementarFrequenciaK0(char simbolo);
      void ordenarK0PorFrequencia();
      vector<double> getFrequenciasOrdenadasExcluidasK0() const;
      int getPosicaoFiltradaK0(char simbolo) const;
      bool verificarSimboloExisteK0(char simbolo) const;
      string chamarROK0(char simboloNuncaVisto);
      string gerarCodigoK0(char simboloDesejado);



    // Métodos básicos
    bool verificarCriarK1(string& contexto);
    bool verificarCriarK2(string& contexto);
    bool verificarCriarK3(string& contexto);
    bool verificarCriarK4(string& contexto);
    bool verificarCriarK5(string& contexto);

    // Operações para K1-K5
    bool adicionarSimboloK1(string& contexto, char simbolo);
    bool incrementarFrequenciaK1(string& contexto, char simbolo);
    void ordenarPorFrequenciaK1(string& contexto);
    bool verificarSeSimboloExisteK1(string& contexto, char simbolo);
    vector<double> getFrequenciasOrdenadasExcluidasK1(string& contexto);
    int getPosicaoOrdenadaExcluidosK1(string& contexto, char simbolo);
    void atualizarTabelaK1(string& contexto, char simbolo);
    string getTodosSimbolosK1(string& contexto);
    bool verificarERemoverRSeNecessarioK1(string& contexto);
    
    bool adicionarSimboloK2(string& contexto, char simbolo);
    bool incrementarFrequenciaK2(string& contexto, char simbolo);
    void ordenarPorFrequenciaK2(string& contexto);
    bool verificarSeSimboloExisteK2(string& contexto, char simbolo);
    vector<double> getFrequenciasOrdenadasExcluidasK2(string& contexto);
    int getPosicaoOrdenadaExcluidosK2(string& contexto, char simbolo);
    void atualizarTabelaK2(string& contexto, char simbolo);
    string getTodosSimbolosK2(string& contexto);
    bool verificarERemoverRSeNecessarioK2(string& contexto);
    
    bool adicionarSimboloK3(string& contexto, char simbolo);
    bool incrementarFrequenciaK3(string& contexto, char simbolo);
    void ordenarPorFrequenciaK3(string& contexto);
    bool verificarSeSimboloExisteK3(string& contexto, char simbolo);
    vector<double> getFrequenciasOrdenadasExcluidasK3(string& contexto);
    int getPosicaoOrdenadaExcluidosK3(string& contexto, char simbolo);
    void atualizarTabelaK3(string& contexto, char simbolo);
    string getTodosSimbolosK3(string& contexto);
    bool verificarERemoverRSeNecessarioK3(string& contexto);
    
    bool adicionarSimboloK4(string& contexto, char simbolo);
    bool incrementarFrequenciaK4(string& contexto, char simbolo);
    void ordenarPorFrequenciaK4(string& contexto);
    bool verificarSeSimboloExisteK4(string& contexto, char simbolo);
    vector<double> getFrequenciasOrdenadasExcluidasK4(string& contexto);
    int getPosicaoOrdenadaExcluidosK4(string& contexto, char simbolo);
    void atualizarTabelaK4(string& contexto, char simbolo);
    string getTodosSimbolosK4(string& contexto);
    bool verificarERemoverRSeNecessarioK4(string& contexto);
    
    bool adicionarSimboloK5(string& contexto, char simbolo);
    bool incrementarFrequenciaK5(string& contexto, char simbolo);
    void ordenarPorFrequenciaK5(string& contexto);
    bool verificarSeSimboloExisteK5(string& contexto, char simbolo);
    vector<double> getFrequenciasOrdenadasExcluidasK5(string& contexto);
    int getPosicaoOrdenadaExcluidosK5(string& contexto, char simbolo);
    void atualizarTabelaK5(string& contexto, char simbolo);
    string getTodosSimbolosK5(string& contexto);
    bool verificarERemoverRSeNecessarioK5(string& contexto);

    void setSimbolosParaExclusao(string& simbolos);
    void zerarSimbolosParaExclusao();

    string gerarCodigoK5(string& contexto, char simboloDesejado);
    string gerarCodigoK4(string& contexto, char simboloDesejado); 
    string gerarCodigoK3(string& contexto, char simboloDesejado);
    string gerarCodigoK2(string& contexto, char simboloDesejado);
    string gerarCodigoK1(string& contexto, char simboloDesejado);
    string gerarCodigoK0(string& contexto, char simboloDesejado);  

    void atualizarContextos(string& contexto, char simboloDesejado);
    char getSimboloK0PorPosicao(int);

private:
    void criarContextoK1(string& contexto);
    void criarContextoK2(string& contexto);
    void criarContextoK3(string& contexto);
    void criarContextoK4(string& contexto);
    void criarContextoK5(string& contexto);
};

#endif