#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <filesystem> // Para verificar o diretório atual

using namespace std;

// Função que filtra o texto
void filtrar_arquivo(const string & arquivo_entrada, const string & arquivo_saida) {
    ifstream entrada(arquivo_entrada);
    ofstream saida(arquivo_saida);
    
    if (!entrada.is_open()) {
        cerr << "Erro ao abrir o arquivo de entrada: " << arquivo_entrada << endl;
        return;
    }
    
    if (!saida.is_open()) {
        cerr << "Erro ao abrir o arquivo de saída: " << arquivo_saida << endl;
        return;
    }

    char c;
    while (entrada.get(c)) {
        c = tolower(c);

        if ((c >= 'a' && c <= 'z') || c == ' ') {
            saida << c;
        }
    }

    if (entrada.bad()) {
        cerr << "Erro durante a leitura do arquivo de entrada." << endl;
    }

    entrada.close();
    saida.close();
}

int main() {
    string arquivo_entrada = "teste.txt";
    string arquivo_saida = "texto_filtrado.txt";


    filtrar_arquivo(arquivo_entrada, arquivo_saida);

    return 0;
}