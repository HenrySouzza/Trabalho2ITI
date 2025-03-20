#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <algorithm>
#include <unordered_map>
#include "k_1.h"
using namespace std;


char substituir_caracteres_especiais(char c) {
    static const unordered_map<char, char> mapa_caracteres = {
        {'á', 'a'}, {'à', 'a'}, {'ã', 'a'}, {'â', 'a'},
        {'é', 'e'}, {'ê', 'e'}, {'í', 'i'}, {'ó', 'o'},
        {'ô', 'o'}, {'õ', 'o'}, {'ú', 'u'}, {'ü', 'u'},
        {'ç', 'c'}, {'Á', 'a'}, {'À', 'a'}, {'Ã', 'a'},
        {'Â', 'a'}, {'É', 'e'}, {'Ê', 'e'}, {'Í', 'i'},
        {'Ó', 'o'}, {'Ô', 'o'}, {'Õ', 'o'}, {'Ú', 'u'},
        {'Ü', 'u'}, {'Ç', 'c'}
    };
    auto it = mapa_caracteres.find(c);
    if (it != mapa_caracteres.end()) {
        return it->second;
    }
    return c;
}

void limpar_texto(ifstream& arquivo_entrada, ofstream& arquivo_saida) {
    char c;
    while (arquivo_entrada.get(c)) {
        c = substituir_caracteres_especiais(c);
        c = tolower(c);
        if ((c >= 'a' && c <= 'z') || c == ' ') {
            arquivo_saida << c;
        } else if (c == '\n') {
            arquivo_saida << ' ';
        }
    }
    arquivo_entrada.close();
    arquivo_saida.close();
}

int main() {
    ifstream arquivo("MemoriasPostumas.txt");
    if (!arquivo) {
        cerr << "Erro ao abrir o arquivo de entrada!" << endl;
        return 1;
    }
    ofstream arquivo_saida("saida.txt");
    if (!arquivo_saida) {
        cerr << "Erro ao abrir o arquivo de saída!" << endl;
        return 1;
    }
    limpar_texto(arquivo, arquivo_saida);

    return 0;
}