#include "k_1.h"
#include <iostream>
#include <string>

using namespace std;

ContextoMenos1::ContextoMenos1(){

    caracteresNaoVistos = 27;
    caracteres[0] = Caracter('a');
    caracteres[1] = Caracter('b');
    caracteres[2] = Caracter('c');
    caracteres[3] = Caracter('d');
    caracteres[4] = Caracter('e');
    caracteres[5] = Caracter('f');
    caracteres[6] = Caracter('g');
    caracteres[7] = Caracter('h');
    caracteres[8] = Caracter('i');
    caracteres[9] = Caracter('j');
    caracteres[10] = Caracter('k');
    caracteres[11] = Caracter('l');
    caracteres[12] = Caracter('m');
    caracteres[13] = Caracter('n');
    caracteres[14] = Caracter('o');
    caracteres[15] = Caracter('p');
    caracteres[16] = Caracter('q');
    caracteres[17] = Caracter('r');
    caracteres[18] = Caracter('s');
    caracteres[19] = Caracter('t');
    caracteres[20] = Caracter('u');
    caracteres[21] = Caracter('v');
    caracteres[22] = Caracter('w');
    caracteres[23] = Caracter('x');
    caracteres[24] = Caracter('y');
    caracteres[25] = Caracter('z');
    caracteres[26] = Caracter(' ');
    
};

string ContextoMenos1::getCodigoNuncaVisto(char simbolo){
    int posicao = 0;
    for(int i = 0; i < 27; i++){
        if(caracteres[i].simbolo == simbolo){
            caracteres[i].jaVisto = true;
            caracteresNaoVistos--;
            break;
        }else{
            if(caracteres[i].jaVisto == false)
                posicao++;
            }
        }
        
    string binario = "";
    int aux = caracteresNaoVistos;
    if (posicao == 0) {
        binario = "0";
    }else{
        while (posicao > 0) {
            binario = to_string(posicao % 2) + binario;
            posicao = posicao / 2;
        }
    }
    int totalDeBits=0;
    while (aux/2 > 0) {
        aux = aux/2;
        totalDeBits++;
    }
    totalDeBits = totalDeBits - binario.size();
    for (int i = 0; i <= totalDeBits; i++) {
        binario = "0" + binario;
    }
        return binario;
}
