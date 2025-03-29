#include "k2.h"
#include <algorithm>

K2::K2() : totalSimbolosLidos(0){
    for(auto& pair : contextos){
        pair.second.simbolos[0].simbolo = 'R';
    }
}

void K2:: adicionarSimbolo(const string& contexto, char simbolo){
    ContextoK2& ctx = contextos[contexto];
    int indice = 28 - ctx.simbolosNuncaVistos;
    ctx.simbolos[indice].simbolo = simbolo;
    ctx.simbolos[indice].frequencia++;
    ctx.simbolosNuncaVistos--;
}

void K2::ordenarSimbolos(ContextoK2& contexto) {
    int tamanho = 28 - contexto.simbolosNuncaVistos;
    sort(contexto.simbolos, contexto.simbolos + tamanho, [](SimbolosK2 a, SimbolosK2 b) {
        return a.frequencia > b.frequencia;
    });
}

int K2::posicaoSimbolo(const ContextoK2& contexto, char simbolo){
    int tamanho = 28 - contexto.simbolosNuncaVistos;
    for(int i=0; i<tamanho; i++){
        if(contexto.simbolos[i].simbolo == simbolo){
            return i;
        }
    }
    return -1;
}

string K2::chamarRO(const string& contexto, char simboloNuncaVisto){
    ContextoK2& ctx = contextos[contexto];
    string codigo = arvoreCodigoSimbolo(ctx, posicaoSimbolo(ctx, 'R'));
    ctx.simbolos[posicaoSimbolo(ctx, 'R')].frequencia++;


    char contextoK1 = contexto[1];
    string codigoDoNuncavisto = contextoMenos1.getCodigoNuncaVisto(simboloNuncaVisto);
    codigo = codigo + "" + codigoDoNuncavisto;
    adicionarSimbolo(contexto, simboloNuncaVisto);

    if(ctx.simbolos[posicaoSimbolo(ctx, 'R')].frequencia == 27){
        ctx.simbolos[posicaoSimbolo(ctx, 'R')].frequencia = 0;
        ctx.simbolosNuncaVistos--;
    }

    return codigo;
}

vector<int> K2::getFrequencias(const ContextoK2& contexto){
    int tamanho = 28 - contexto.simbolosNuncaVistos;
    vector<int> frequencias(tamanho);
    for(int i=0; i<tamanho; i++){
        frequencias[i] = contexto.simbolos[i].frequencia;
    }
    return frequencias;
}

void K2::adicionarFrequencia(ContextoK2& contexto, int posicao){
    contexto.simbolos[posicao].frequencia++;
}

string K2::arvoreCodigoSimbolo(ContextoK2& contexto, int posicao){
    vector<int> valores = getFrequencias(contexto);
    return obterCodigoHuffman(valores, posicao);
}

string K2::gerarCodigo(const string& contextoAnterior, string palavra){
    char simbolo = palavra[0];
   
    if(contextoAnterior.length() <2){
        return contextoK1.gerarCodigo(contextoAnterior[0], palavra);
    }
    
    // Verifica se o contexto existe, se não, cria
    if (contextos.find(contextoAnterior) == contextos.end()) {
        cout << "Criando novo contexto K2: " << contextoAnterior << endl;
        contextos[contextoAnterior] = ContextoK2();
        contextos[contextoAnterior].simbolos[0].simbolo = 'R';
        contextos[contextoAnterior].contextoAnterior = contextoAnterior;
    }

    ContextoK2& ctx = contextos[contextoAnterior];
    ordenarSimbolos(ctx);


    string codigo = "";
    int posicao = posicaoSimbolo(ctx, simbolo);
    
    if (posicao == -1) {
        codigo = chamarRO(contextoAnterior, simbolo);
    } else {
        codigo = arvoreCodigoSimbolo(ctx, posicao);
        adicionarFrequencia(ctx, posicao);
    }
    
    return codigo;
}