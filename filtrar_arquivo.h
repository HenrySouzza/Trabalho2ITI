#ifndef filtrar_arquivo_H
#define filtrar_arquivo_H

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <algorithm>
#include <unordered_map>
#include "k_1.h"
using namespace std;

char* filtrar_arquivo(char* nome_arquivo, char* palavra_chave);
char substituir_caracteres_especiais(char c);
void limpar_texto(ifstream& arquivo_entrada, ofstream& arquivo_saida);

#endif