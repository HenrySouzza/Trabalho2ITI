#include "k0.h"



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
    codigo = codigo + " " + codigoDoNuncavisto;
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
    string palavra = "abracadabra";

    LeitorDeArquivo leitor("saida.txt");

    for(int i = 0; i < 28; i++){
        leitor.atualizarLetras();
        palavra = leitor.getUltimasSaidas(0);
        cout << palavra<< " -> " <<k0.gerarCodigo(palavra) << endl;
    }

    return 0;
}











