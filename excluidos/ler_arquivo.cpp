#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <algorithm>
#include <vector>
using namespace std;

void ler_arquivo(int valor_k){
    ifstream arquivo("saida.txt");
    char c;
    vector<string> palavras;
    string palavra;

    while(arquivo.get(c)){
        if (isalpha(c)) {
            palavra += c;
            if (palavra.size() == valor_k) {
                palavras.push_back(palavra);
                palavra = palavra.substr(1); 
            }
        } else if (!palavra.empty()) {
            palavras.push_back(palavra);
            palavra.clear();
        }
    }

    // Adiciona a última palavra se não estiver vazia
    if (!palavra.empty()) {
        palavras.push_back(palavra);
    }

    // Exibe as palavras ou n-gramas
    for (const auto& p : palavras) {
        cout << p << endl;
    }

}

int main(){
    int valor_k = 0;
    ler_arquivo(valor_k);
    return 0;
}