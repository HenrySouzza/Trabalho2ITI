#include "leitor.h"

LeitorDeArquivo::LeitorDeArquivo(const std::string& caminho) {
    caminhoArquivo = caminho;
    arquivo.open(caminhoArquivo);

    // Verifica se o arquivo foi aberto corretamente
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo!" << std::endl;
    }
}

char LeitorDeArquivo::lerProximaLetra() {
    char letra;
    if (arquivo.get(letra)) {
        return letra; // Retorna a próxima letra lida
    }
    return '\0'; // Retorna null se o arquivo terminou
}

bool LeitorDeArquivo::temMaisLetras() {
    return !arquivo.eof();
}

void LeitorDeArquivo::atualizarLetras() {
    ultimasSaidas[5] = ultimasSaidas[4];
    ultimasSaidas[4] = ultimasSaidas[3];    
    ultimasSaidas[3] = ultimasSaidas[2];    
    ultimasSaidas[2] = ultimasSaidas[1];
    ultimasSaidas[1] = ultimasSaidas[0];
    ultimasSaidas[0] = lerProximaLetra();
}

string LeitorDeArquivo::getContexto(int contexto){
    string saidas = "";
    for(int i = contexto; i > 0; i--){
        saidas += ultimasSaidas[i];
    }
    return saidas;
}

char LeitorDeArquivo::getUltimasSaidas(){
    return ultimasSaidas[0];
}
