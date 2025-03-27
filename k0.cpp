#include "k0.h"
#include "conversor.h"
#include <chrono>
#include <cmath>


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

int main(){
    K0 k0;
    string palavra;

    double total_de_bits = 0;
    int total_de_caracteres = 0;
    vector<int> frequencias(256,0);
    high_resolution_clock::time_point inicio = high_resolution_clock::now();

    LeitorDeArquivo leitor("saida.txt");
    conversor conversor("saida.bin");


    string bufferBinario;

    while(leitor.temMaisLetras()) {
        leitor.atualizarLetras();
        palavra = leitor.getUltimasSaidas(0);

        char c = palavra[0];
        frequencias[c]++;
        total_de_caracteres++;
        string codigo = k0.gerarCodigo(palavra);
        total_de_bits += codigo.size();

        conversor.adicionarcodigo(codigo);
      
    }

    conversor.fechararquivo();
    high_resolution_clock::time_point fim = high_resolution_clock::now();
    auto duracao_ns = duration_cast<nanoseconds>(fim - inicio).count();
    double duracao_segundos = duracao_ns / 1'000'000'000.0;
    
    double entropia = 0;
    for(int i=0; i<256; i++){
        if(frequencias[i] != 0){
            double probabilidade = frequencias[i]/(double)total_de_caracteres;
            entropia += probabilidade * log2(1/probabilidade);
        }
    }

    double comprimento_medio = total_de_bits/total_de_caracteres;

    // Exibição das métricas
    cout << "Tempo de compressão: " << duracao_segundos << " s" << endl;
    cout << "Entropia da fonte: " << entropia << " bits/simbolo" << endl;
    cout << "Comprimento médio do código: " << comprimento_medio << " bits/simbolo" << endl;
 
    return 0;
}











