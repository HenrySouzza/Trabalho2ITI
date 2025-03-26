#include "conversor.h"
#include <bitset>

using namespace std;

conversor::conversor(const string& arquivodesaida){
    arquivo.open(arquivodesaida, ios::binary);
    buffer = "";
}

conversor::~conversor(){
    fechararquivo();
    if(arquivo.is_open()){
        arquivo.close();
    }
}

void conversor::adicionarcodigo(const string& codigo){
    buffer += codigo;
    while(buffer.length() >= 8){
        string byteStr = buffer.substr(0, 8);
        bitset<8> bits(byteStr);
        char byte = static_cast<char>(bits.to_ulong());
        arquivo.write(&byte, sizeof(byte));
        buffer.erase(0, 8);
    }
}

void conversor::fechararquivo(){
    if(!buffer.empty()){
        while(buffer.length() < 8){
            buffer += '0';
        }
        bitset<8> bits(buffer);
        char byte = static_cast<char>(bits.to_ulong());
        arquivo.write(&byte, sizeof(byte));
    }
}