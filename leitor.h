#ifndef LEITOR_H
#define LEITOR_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class LeitorDeArquivo {
private:
    std::ifstream arquivo;
    std::string caminhoArquivo;
    char ultimasSaidas[6];

public:
    // Construtor que recebe o caminho do arquivo
    LeitorDeArquivo(const std::string& caminho);

    // Função para ler a próxima letra do arquivo
    char lerProximaLetra();

    // Função para verificar se o arquivo ainda tem mais letras
    bool temMaisLetras();

    void atualizarLetras();

    string getUltimasSaidas(int contexto);
};

#endif
