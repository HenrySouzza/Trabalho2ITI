#include "k1.h"

K1::K1() : totalSimbolosLidos(0) {
    for (auto& pair : contextos) {
        pair.second.simbolos[0].simbolo = 'R';
    }
}

void K1::adicionarSimbolo(char contexto, char simbolo) {
    ContextoK1& ctx = contextos[contexto];
    int indice = 28 - ctx.simbolosNuncaVistos;
    ctx.simbolos[indice].simbolo = simbolo;
    ctx.simbolos[indice].frequencia++;
    ctx.simbolosNuncaVistos--;
}

void K1::ordenarSimbolos(ContextoK1& contexto) {
    int tamanho = 28 - contexto.simbolosNuncaVistos;
    sort(contexto.simbolos, contexto.simbolos + tamanho, [](SimbolosK1 a, SimbolosK1 b) {
        return a.frequencia > b.frequencia;
    });
}

int K1::posicaoSimbolo(const ContextoK1& contexto, char simbolo) {
    int tamanho = 28 - contexto.simbolosNuncaVistos;
    for (int i = 0; i < tamanho; i++) {
        if (contexto.simbolos[i].simbolo == simbolo) {
            return i;
        }
    }
    return -1;
}

string K1::chamarRO(char contexto, char simboloNuncaVisto) {
    ContextoK1& ctx = contextos[contexto];
    string codigo = arvoreCodigoSimbolo(ctx, posicaoSimbolo(ctx, 'R'));
    ctx.simbolos[posicaoSimbolo(ctx, 'R')].frequencia++;

    string codigoDoNuncavisto = contextoMenos1.getCodigoNuncaVisto(simboloNuncaVisto);
    codigo = codigo + "" + codigoDoNuncavisto;
    adicionarSimbolo(contexto, simboloNuncaVisto);

    if (ctx.simbolos[posicaoSimbolo(ctx, 'R')].frequencia == 27) {
        ctx.simbolos[posicaoSimbolo(ctx, 'R')].frequencia = 0;
        ctx.simbolosNuncaVistos--;
    }

    return codigo;
}

vector<int> K1::getFrequencias(const ContextoK1& contexto) {
    int tamanho = 28 - contexto.simbolosNuncaVistos;
    vector<int> frequencias(tamanho);
    for (int i = 0; i < tamanho; i++) {
        frequencias[i] = contexto.simbolos[i].frequencia;
    }
    return frequencias;
}

void K1::adicionarFrequencia(ContextoK1& contexto, int posicao) {
    contexto.simbolos[posicao].frequencia++;
}

string K1::arvoreCodigoSimbolo(ContextoK1& contexto, int posicao) {
    vector<int> valores = getFrequencias(contexto);
    return obterCodigoHuffman(valores, posicao);
}

string K1::gerarCodigo(char contextoAnterior, string palavra) {
    char simbolo = palavra[0];
    
    // Se não houver contexto anterior, usa K0
    if (contextoAnterior == '\0') {
        return contextoK0.gerarCodigo(palavra);
    }

    // Verifica se o contexto existe, se não, cria
    if (contextos.find(contextoAnterior) == contextos.end()) {
        contextos[contextoAnterior] = ContextoK1();
        contextos[contextoAnterior].simbolos[0].simbolo = 'R';
        contextos[contextoAnterior].contextoAnterior = contextoAnterior;
    }

    ContextoK1& ctx = contextos[contextoAnterior];
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