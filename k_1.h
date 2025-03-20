#ifndef K_1_H  
#define K_1_H

#include <string>
using namespace std;


class Caracter {
public:
    char simbolo;
    bool jaVisto;
    Caracter() : simbolo(' '), jaVisto(false) {}
    Caracter(char s) : simbolo(s), jaVisto(false) {}
};

class ContextoMenos1 {
private:
    Caracter caracteres[27];
    int caracteresNaoVistos;
public:
    ContextoMenos1();
    ~ContextoMenos1() {}
    string getCodigoNuncaVisto(char simbolo);
};

#endif