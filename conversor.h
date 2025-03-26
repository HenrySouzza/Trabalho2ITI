#ifndef conversor_H
#define conversor_H
#include <string>
#include <fstream>

using namespace std;

class conversor{
    public:
    explicit conversor(const string& arquivodesaida);
    ~conversor();
    void adicionarcodigo(const string& codigo);
    void fechararquivo();

    private:
    ofstream arquivo;
    string buffer; 
};


#endif