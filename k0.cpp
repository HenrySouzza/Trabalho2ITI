#include "k0.h"
#include "conversor.h"
#include <chrono>
#include <cmath>
#include "k1.h"
#include "k2.h"


using namespace std::chrono;

K0::K0(){
    simbolosNuncaVistos=27;
    totalSimbolosLidos=0;
    simbolo[0].simbolo = 'R';
}
int K0::getPrimeiraPosicaoVazia(){
    return 28 - simbolosNuncaVistos ;
}
void K0::adicionarSimbolo(char simbolo){
    int indice = getPrimeiraPosicaoVazia();
    this->simbolo[indice].simbolo = simbolo;
    this->simbolo[indice].frequencia++;
    simbolosNuncaVistos--;
}
void K0::ordenarSimbolos(){
    sort(simbolo, simbolo+getPrimeiraPosicaoVazia(), [](SimbolosK0 a, SimbolosK0 b){
        return a.frequencia > b.frequencia;
    });
}
int K0::posicaoSimbolo(char simbolo){
    for(int i=0; i<getPrimeiraPosicaoVazia(); i++){
        if(this->simbolo[i].simbolo == simbolo){
            return i;
        }
    }
    return -1;
}
string K0::chamarRO(char simboloNuncaVisto){
    string codigo = "";
    codigo = arvoreCodigoSimbolo(posicaoSimbolo('R'));
    simbolo[posicaoSimbolo('R')].frequencia++;

    string codigoDoNuncavisto = contextoMenos1.getCodigoNuncaVisto(simboloNuncaVisto);
    codigo = codigo + "" + codigoDoNuncavisto;
    adicionarSimbolo(simboloNuncaVisto);

    if(simbolo[posicaoSimbolo('R')].frequencia == 27){
       simbolo[posicaoSimbolo('R')].frequencia = 0;
       simboloNuncaVisto--;
    }

    return codigo;
}
vector<int> K0::getFrequencias(){
    int tamanho = getPrimeiraPosicaoVazia();
    vector<int> frequencias(tamanho);
    //cout << "Tabela de frequencias" << endl;
    for(int i=0; i<tamanho; i++){
        frequencias[i] = simbolo[i].frequencia;
        //cout << i <<". " << simbolo[i].simbolo <<" casa. Frequencia -> " << frequencias[i] << endl;
    }
    return frequencias;
}
void K0::adicionarFrequencia(int posicao){
    simbolo[posicao].frequencia++;
}

string K0::arvoreCodigoSimbolo(int posicao){
    vector<int> valores(27-simbolosNuncaVistos);
    valores = getFrequencias();
    return obterCodigoHuffman(valores, posicao);
}

string K0::gerarCodigo(string palavra){
    ordenarSimbolos();
    char simbolo = palavra[0];
    string codigo = "";
    int posicao = posicaoSimbolo(simbolo);
    //cout << "Posicao do simbolo " << simbolo << " -> " << posicao << endl;
    if(posicao == -1){
        codigo = chamarRO(simbolo);
    }else{
        codigo = arvoreCodigoSimbolo(posicao);
        adicionarFrequencia(posicao);
    }
    
    return codigo;
}

int main() {
    K0 k0;
    K1 k1;
    K2 k2;
    string palavra;
    char contextoAnterior = '\0';

    double total_de_bits_k0 = 0;
    double total_de_bits_k1 = 0;
    double total_de_bits_k2 = 0;
    int total_de_caracteres = 0;
    vector<int> frequencias(256, 0);
    high_resolution_clock::time_point inicio = high_resolution_clock::now();

    LeitorDeArquivo leitor("saida.txt");
    conversor conversorK0("saida.bin");
    conversor conversorK1("saida2.bin");
    conversor conversorK2("saida3.bin");

    while (leitor.temMaisLetras()) {
        leitor.atualizarLetras();
        palavra = leitor.getUltimasSaidas(0);
        char c = palavra[0];

        frequencias[c]++;
        total_de_caracteres++;

        // Processa com K0
        string codigoK0 = k0.gerarCodigo(palavra);
        total_de_bits_k0 += codigoK0.size();
        conversorK0.adicionarcodigo(codigoK0);

        // Processa com K1
        string codigoK1 = k1.gerarCodigo(contextoAnterior, palavra);
        total_de_bits_k1 += codigoK1.size();
        conversorK1.adicionarcodigo(codigoK1);

        // Processa com K2
        string codigoK2 = k2.gerarCodigo(string(1, contextoAnterior), palavra);
        total_de_bits_k2 += codigoK2.size();
        conversorK2.adicionarcodigo(codigoK2);

        // Atualiza contexto anterior para próxima iteração
        contextoAnterior = c;
    }

    conversorK0.fechararquivo();
    conversorK1.fechararquivo();
    conversorK2.fechararquivo();
    
    high_resolution_clock::time_point fim = high_resolution_clock::now();
    auto duracao_ns = duration_cast<nanoseconds>(fim - inicio).count();
    double duracao_segundos = duracao_ns / 1'000'000'000.0;
    
    double entropia = 0;
    for (int i = 0; i < 256; i++) {
        if (frequencias[i] != 0) {
            double probabilidade = frequencias[i] / (double)total_de_caracteres;
            entropia += probabilidade * log2(1 / probabilidade);
        }
    }

    double comprimento_medio_k0 = total_de_bits_k0 / total_de_caracteres;
    double comprimento_medio_k1 = total_de_bits_k1 / total_de_caracteres;
    double comprimento_medio_k2 = total_de_bits_k2 / total_de_caracteres;

    // Exibição das métricas
    cout << "Tempo de compressão: " << duracao_segundos << " s" << endl;
    cout << "Entropia da fonte: " << entropia << " bits/simbolo" << endl;
    cout << "Comprimento médio do código K0: " << comprimento_medio_k0 << " bits/simbolo" << endl;
    cout << "Comprimento médio do código K1: " << comprimento_medio_k1 << " bits/simbolo" << endl;
    cout << "Comprimento médio do código K2: " << comprimento_medio_k2 << " bits/simbolo" << endl;
    cout << "Taxa de compressão K0: " << (total_de_caracteres * 8) / total_de_bits_k0 << endl;
 
    return 0;
}











