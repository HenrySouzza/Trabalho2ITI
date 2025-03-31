#include "GerenciadorContextos.h"

using namespace std::chrono;

// Implementação dos métodos básicos
bool GerenciadorContextos::verificarCriarK1(string& contexto) {
    if (!contexto.empty() && tabelaContextosK1.find(contexto) == tabelaContextosK1.end()) {
        criarContextoK1(contexto);
        return false;
    }else {
        return true; // Contexto já existe
    }
}

bool GerenciadorContextos::verificarCriarK2(string& contexto) {
    if (!contexto.empty() && tabelaContextosK2.find(contexto) == tabelaContextosK2.end()) {
        criarContextoK2(contexto);
        return false;
    }else {
        return true; // Contexto já existe
    }
}

bool GerenciadorContextos::verificarCriarK3(string& contexto) {
    if (!contexto.empty() && tabelaContextosK3.find(contexto) == tabelaContextosK3.end()) {
        criarContextoK3(contexto);
        return false;
    }else {
        return true; // Contexto já existe
    }
}

bool GerenciadorContextos::verificarCriarK4(string& contexto) {
    if (!contexto.empty() && tabelaContextosK4.find(contexto) == tabelaContextosK4.end()) {
        criarContextoK4(contexto);
        return false;
    }else {
        return true; // Contexto já existe
    }
}

bool GerenciadorContextos::verificarCriarK5(string& contexto) {
    if (!contexto.empty() && tabelaContextosK5.find(contexto) == tabelaContextosK5.end()) {
        criarContextoK5(contexto);
        return false;
    }else {
        return true; // Contexto já existe
    }
}

// Métodos privados de criação
void GerenciadorContextos::criarContextoK1(string& contexto) {
    tabelaContextosK1[contexto] = {{'R', 0.0}};
}

void GerenciadorContextos::criarContextoK2(string& contexto) {
    tabelaContextosK2[contexto] = {{'R', 0.0}};
}

void GerenciadorContextos::criarContextoK3(string& contexto) {
    tabelaContextosK3[contexto] = {{'R', 0.0}};
}

void GerenciadorContextos::criarContextoK4(string& contexto) {
    tabelaContextosK4[contexto] = {{'R', 0.0}};
}

void GerenciadorContextos::criarContextoK5(string& contexto) {
    tabelaContextosK5[contexto] = {{'R', 0.0}};
}

// Implementação de K0

// Construtor
GerenciadorContextos::GerenciadorContextos() : proximaPosicaoLivre(1) {
    simbolosK0[0] = {'R', 0.0}; // Posição fixa para 'R'
    for (int i = 1; i < 28; ++i) {
        simbolosK0[i] = {'\0', 0.0}; // Inicializa como vazio
    }
}

// Adiciona símbolo na primeira posição vazia
bool GerenciadorContextos::adicionarSimboloK0(char simbolo) {
    if (proximaPosicaoLivre >= 28) return false;
    
    // Verifica se já existe
    for (int i = 0; i < proximaPosicaoLivre; ++i) {
        if (simbolosK0[i].representacao == simbolo) {
            return false;
        }
    }
    
    simbolosK0[proximaPosicaoLivre++] = {simbolo, 1.0};
    ordenarK0PorFrequencia();
    return true;
}

// Incrementa frequência do símbolo
bool GerenciadorContextos::incrementarFrequenciaK0(char simbolo) {
    for (int i = 0; i < proximaPosicaoLivre; ++i) {
        if (simbolosK0[i].representacao == simbolo) {
            simbolosK0[i].frequencia += 1.0;
            ordenarK0PorFrequencia();
            return true;
        }
    }
    return false;
}

// Ordena do maior para o menor (exceto 'R' na posição 0)
void GerenciadorContextos::ordenarK0PorFrequencia() {
    if (proximaPosicaoLivre <= 1) return;
    
    // Ordena com critério composto: frequência decrescente -> alfabético crescente
    sort(simbolosK0, simbolosK0 + proximaPosicaoLivre, [](const Simbolo& a, const Simbolo& b) {
        if (a.frequencia == b.frequencia) {
            return a.representacao < b.representacao; // Ordem alfabética se frequências iguais
        }
        return a.frequencia > b.frequencia; // Primeiro ordena por frequência decrescente
    });
}

// Retorna posição ignorando símbolos excluídos (0-based)
int GerenciadorContextos::getPosicaoFiltradaK0(char simbolo) const {
    int posFiltrada = 0;
    for (int i = 0; i < proximaPosicaoLivre; ++i) {
        char s = simbolosK0[i].representacao;
        // Ignora símbolos na lista de exclusão e '\0' (vazios)
        if (s == '\0' || simbolosParaExclusao.find(s) != string::npos) {
            continue;
        }
        if (s == simbolo) {
            return posFiltrada;
        }
        posFiltrada++;
    }
    return -1; // Não encontrado
}

// Retorna vetor de frequências ordenado (sem excluídos)
vector<double> GerenciadorContextos::getFrequenciasOrdenadasExcluidasK0() const {
    vector<Simbolo> filtrados;
    for (int i = 0; i < proximaPosicaoLivre; ++i) {
        char s = simbolosK0[i].representacao;
        double freq = simbolosK0[i].frequencia;
        

        if (s != '\0' && 
            simbolosParaExclusao.find(s) == string::npos &&
            freq > 0.0) {
            filtrados.push_back(simbolosK0[i]);
        }
    }
    
    // Ordena decrescente por frequência
    sort(filtrados.begin(), filtrados.end());
    
    // Extrai apenas as frequências
    vector<double> frequencias;
    for (const auto& s : filtrados) {
        frequencias.push_back(s.frequencia);
    }
    
    return frequencias;
}

bool GerenciadorContextos::verificarSimboloExisteK0(char simbolo)const{
    for (int i = 0; i < proximaPosicaoLivre; ++i) {
        char s = simbolosK0[i].representacao;
        // Verifica se é o símbolo procurado, não é vazio e não está excluído
        if (s == simbolo && s != '\0') {
            return true;
        }
    }
    return false;
}

string GerenciadorContextos::chamarROK0(char simboloNuncaVisto) {
    string codigo = "";
    ordenarK0PorFrequencia();
    auto frequencias = getFrequenciasOrdenadasExcluidasK0();
    codigo += obterCodigoHuffman(frequencias, getPosicaoFiltradaK0('R'));
    incrementarFrequenciaK0('R');

    simbolosParaExclusao = "";

    if(simbolosK0[getPosicaoFiltradaK0('R')].frequencia == 27.0) {
        simbolosK0[getPosicaoFiltradaK0('R')].frequencia = 0.0;
        simboloNuncaVisto--;
    }

    // Adiciona o código do símbolo nunca visto
    codigo += "" + contextoMenos1.getCodigoNuncaVisto(simboloNuncaVisto);

    // Adiciona o caracter nunca visto
    adicionarSimboloK0(simboloNuncaVisto);
    
    return codigo;

 
}

string GerenciadorContextos::gerarCodigoK0(char simboloDesejado) {
    string codigo = "";
    if(verificarSimboloExisteK0(simboloDesejado)){
        auto frequencias = getFrequenciasOrdenadasExcluidasK0();
        codigo = obterCodigoHuffman(frequencias, getPosicaoFiltradaK0(simboloDesejado));
        incrementarFrequenciaK0(simboloDesejado);
    } else {
        codigo = chamarROK0(simboloDesejado);
    }
    return codigo;
   
}

// Implementação das operações para K1
bool GerenciadorContextos::adicionarSimboloK1(string& contexto, char simbolo) {
    auto it = tabelaContextosK1.find(contexto);
    if (it != tabelaContextosK1.end()) {
        for (auto& s : it->second) {
            if (s.representacao == simbolo) return false;
        }
        it->second.push_back({simbolo, 1.0});
        return true;
    }
    return false;
}

bool GerenciadorContextos::incrementarFrequenciaK1(string& contexto, char simbolo) {
    auto it = tabelaContextosK1.find(contexto);
    if (it != tabelaContextosK1.end()) {
        for (auto& s : it->second) {
            if (s.representacao == simbolo) {
                s.frequencia += 1.0;
                return true;
            }
        }
    }
    return false;
}

void GerenciadorContextos::ordenarPorFrequenciaK1(string& contexto) {
    auto it = tabelaContextosK1.find(contexto);
    if (it != tabelaContextosK1.end()) {
        sort(it->second.begin(), it->second.end());
    }
}

bool GerenciadorContextos::verificarSeSimboloExisteK1(string& contexto, char simbolo){
    // Verifica se o contexto existe
    auto it = tabelaContextosK1.find(contexto);
    if (it != tabelaContextosK1.end()) {
        // Percorre todos os símbolos do contexto
        for (const auto& s : it->second) {
            // Retorna true se encontrar uma representação igual
            if (s.representacao == simbolo) {
                return true;
            }
        }
    }
    return false; // Não encontrou o símbolo ou o contexto não existe
}

vector<double> GerenciadorContextos::getFrequenciasOrdenadasExcluidasK1(string& contexto) {
    vector<double> frequencias;
    auto it = tabelaContextosK1.find(contexto);
    
    if (it != tabelaContextosK1.end()) {
        // Filtra e ordena em uma única operação
        vector<Simbolo> filtrados;
        
        for (const auto& simbolo : it->second) {
            bool naoExcluido = simbolosParaExclusao.find(simbolo.representacao) == string::npos;
            bool frequenciaValida = simbolo.frequencia > 0.0;
            
            if (naoExcluido && frequenciaValida) {
                filtrados.push_back(simbolo);
            }
        }

        
        // Extrai apenas as frequências
        for (const auto& s : filtrados) {
            frequencias.push_back(s.frequencia);
        }
    }
    
    return frequencias;
}

int GerenciadorContextos::getPosicaoOrdenadaExcluidosK1(string& contexto, char simbolo) {
    auto it = tabelaContextosK1.find(contexto);
    if (it != tabelaContextosK1.end()) {
        // Cria cópia filtrada e ordenada
        vector<Simbolo> filtrados;
        for (const auto& s : it->second) {
            if (simbolosParaExclusao.find(s.representacao) == string::npos) {
                filtrados.push_back(s);
            }
        }
        sort(filtrados.begin(), filtrados.end());
        
        // Busca a posição do símbolo
        for (int i = 0; i < filtrados.size(); ++i) {
            if (filtrados[i].representacao == simbolo) {
                return i; // Retorna a posição (0-based)
            }
        }
    }
    return -1; // Não encontrado ou contexto inexistente
}

string GerenciadorContextos::getTodosSimbolosK1(string& contexto) {
    string simbolos;
    auto it = tabelaContextosK1.find(contexto);
    
    if (it != tabelaContextosK1.end()) {
        for (const auto& s : it->second) {
            // Exclui 'R' e quaisquer símbolos em simbolosParaExclusao
            if (s.representacao != 'R' && 
                simbolosParaExclusao.find(s.representacao) == string::npos) {
                simbolos += s.representacao;
            }
        }
    }
    return simbolos;
}

bool GerenciadorContextos::verificarERemoverRSeNecessarioK1(string& contexto) {
    auto it = tabelaContextosK1.find(contexto);
    if (it != tabelaContextosK1.end()) {
        // Procura pelo símbolo 'R' no vetor
        for (auto simbolo_it = it->second.begin(); simbolo_it != it->second.end(); ++simbolo_it) {
            if (simbolo_it->representacao == 'R' && simbolo_it->frequencia == 27.0) {
                it->second.erase(simbolo_it);  // Remove o 'R'
                return true;  // Indica que foi removido
            }
        }
    }
    return false;  // 'R' não foi removido
}

// Implementação para K2
bool GerenciadorContextos::adicionarSimboloK2(string& contexto, char simbolo) {
    auto it = tabelaContextosK2.find(contexto);
    if (it != tabelaContextosK2.end()) {
        for (auto& s : it->second) {
            if (s.representacao == simbolo) return false;
        }
        it->second.push_back({simbolo, 1.0});
        return true;
    }
    return false;
}

bool GerenciadorContextos::incrementarFrequenciaK2(string& contexto, char simbolo) {
    auto it = tabelaContextosK2.find(contexto);
    if (it != tabelaContextosK2.end()) {
        for (auto& s : it->second) {
            if (s.representacao == simbolo) {
                s.frequencia += 1.0;
                return true;
            }
        }
    }
    return false;
}

void GerenciadorContextos::ordenarPorFrequenciaK2(string& contexto) {
    auto it = tabelaContextosK2.find(contexto);
    if (it != tabelaContextosK2.end()) {
        sort(it->second.begin(), it->second.end());
    }
}

bool GerenciadorContextos::verificarSeSimboloExisteK2(string& contexto, char simbolo){
    // Verifica se o contexto existe
    auto it = tabelaContextosK2.find(contexto);
    if (it != tabelaContextosK2.end()) {
        // Percorre todos os símbolos do contexto
        for (const auto& s : it->second) {
            // Retorna true se encontrar uma representação igual
            if (s.representacao == simbolo) {
                return true;
            }
        }
    }
    return false; // Não encontrou o símbolo ou o contexto não existe
}

vector<double> GerenciadorContextos::getFrequenciasOrdenadasExcluidasK2(string& contexto) {
    vector<double> frequencias;
    auto it = tabelaContextosK2.find(contexto);
    
    if (it != tabelaContextosK2.end()) {
        // Faz uma cópia para ordenar sem modificar o original
        vector<Simbolo> copia = it->second;
        sort(copia.begin(), copia.end());
        
        for (const auto& simbolo : copia) {
            // Verifica se o símbolo não está na lista de exclusão
            if (simbolosParaExclusao.find(simbolo.representacao) == string::npos) {
                frequencias.push_back(simbolo.frequencia);
            }
        }
    }
    
    return frequencias;
}

int GerenciadorContextos::getPosicaoOrdenadaExcluidosK2(string& contexto, char simbolo) {
    auto it = tabelaContextosK2.find(contexto);
    if (it != tabelaContextosK2.end()) {
        // Cria cópia filtrada e ordenada
        vector<Simbolo> filtrados;
        for (const auto& s : it->second) {
            if (simbolosParaExclusao.find(s.representacao) == string::npos) {
                filtrados.push_back(s);
            }
        }
        sort(filtrados.begin(), filtrados.end());
        
        // Busca a posição do símbolo
        for (int i = 0; i < filtrados.size(); ++i) {
            if (filtrados[i].representacao == simbolo) {
                return i; // Retorna a posição (0-based)
            }
        }
    }
    return -1; // Não encontrado ou contexto inexistente
}

string GerenciadorContextos::getTodosSimbolosK2(string& contexto) {
    string simbolos;
    auto it = tabelaContextosK2.find(contexto);
    
    if (it != tabelaContextosK2.end()) {
        for (const auto& s : it->second) {
            // Exclui 'R' e quaisquer símbolos em simbolosParaExclusao
            if (s.representacao != 'R' && 
                simbolosParaExclusao.find(s.representacao) == string::npos) {
                simbolos += s.representacao;
            }
        }
    }
    return simbolos;
}

bool GerenciadorContextos::verificarERemoverRSeNecessarioK2(string& contexto) {
    auto it = tabelaContextosK2.find(contexto);
    if (it != tabelaContextosK2.end()) {
        // Procura pelo símbolo 'R' no vetor
        for (auto simbolo_it = it->second.begin(); simbolo_it != it->second.end(); ++simbolo_it) {
            if (simbolo_it->representacao == 'R' && simbolo_it->frequencia == 27.0) {
                it->second.erase(simbolo_it);  // Remove o 'R'
                return true;  // Indica que foi removido
            }
        }
    }
    return false;  // 'R' não foi removido
}

// Implementações para K3
bool GerenciadorContextos::adicionarSimboloK3(string& contexto, char simbolo) {
    auto it = tabelaContextosK3.find(contexto);
    if (it != tabelaContextosK3.end()) {
        for (auto& s : it->second) {
            if (s.representacao == simbolo) return false;
        }
        it->second.push_back({simbolo, 1.0});
        return true;
    }
    return false;
}

bool GerenciadorContextos::incrementarFrequenciaK3(string& contexto, char simbolo) {
    auto it = tabelaContextosK3.find(contexto);
    if (it != tabelaContextosK3.end()) {
        for (auto& s : it->second) {
            if (s.representacao == simbolo) {
                s.frequencia += 1.0;
                return true;
            }
        }
    }
    return false;
}

void GerenciadorContextos::ordenarPorFrequenciaK3(string& contexto) {
    auto it = tabelaContextosK3.find(contexto);
    if (it != tabelaContextosK3.end()) {
        sort(it->second.begin(), it->second.end());
    }
}

bool GerenciadorContextos::verificarSeSimboloExisteK3(string& contexto, char simbolo){
    // Verifica se o contexto existe
    auto it = tabelaContextosK3.find(contexto);
    if (it != tabelaContextosK3.end()) {
        // Percorre todos os símbolos do contexto
        for (const auto& s : it->second) {
            // Retorna true se encontrar uma representação igual
            if (s.representacao == simbolo) {
                return true;
            }
        }
    }
    return false; // Não encontrou o símbolo ou o contexto não existe
}

vector<double> GerenciadorContextos::getFrequenciasOrdenadasExcluidasK3(string& contexto) {
    vector<double> frequencias;
    auto it = tabelaContextosK3.find(contexto);
    
    if (it != tabelaContextosK3.end()) {
        // Faz uma cópia para ordenar sem modificar o original
        vector<Simbolo> copia = it->second;
        sort(copia.begin(), copia.end());
        
        for (const auto& simbolo : copia) {
            // Verifica se o símbolo não está na lista de exclusão
            if (simbolosParaExclusao.find(simbolo.representacao) == string::npos) {
                frequencias.push_back(simbolo.frequencia);
            }
        }
    }
    
    return frequencias;
}

int GerenciadorContextos::getPosicaoOrdenadaExcluidosK3(string& contexto, char simbolo) {
    auto it = tabelaContextosK3.find(contexto);
    if (it != tabelaContextosK3.end()) {
        // Cria cópia filtrada e ordenada
        vector<Simbolo> filtrados;
        for (const auto& s : it->second) {
            if (simbolosParaExclusao.find(s.representacao) == string::npos) {
                filtrados.push_back(s);
            }
        }
        sort(filtrados.begin(), filtrados.end());
        
        // Busca a posição do símbolo
        for (int i = 0; i < filtrados.size(); ++i) {
            if (filtrados[i].representacao == simbolo) {
                return i; // Retorna a posição (0-based)
            }
        }
    }
    return -1; // Não encontrado ou contexto inexistente
}

string GerenciadorContextos::getTodosSimbolosK3(string& contexto) {
    string simbolos;
    auto it = tabelaContextosK3.find(contexto);
    
    if (it != tabelaContextosK3.end()) {
        for (const auto& s : it->second) {
            // Exclui 'R' e quaisquer símbolos em simbolosParaExclusao
            if (s.representacao != 'R' && 
                simbolosParaExclusao.find(s.representacao) == string::npos) {
                simbolos += s.representacao;
            }
        }
    }
    return simbolos;
}

bool GerenciadorContextos::verificarERemoverRSeNecessarioK3(string& contexto) {
    auto it = tabelaContextosK3.find(contexto);
    if (it != tabelaContextosK3.end()) {
        // Procura pelo símbolo 'R' no vetor
        for (auto simbolo_it = it->second.begin(); simbolo_it != it->second.end(); ++simbolo_it) {
            if (simbolo_it->representacao == 'R' && simbolo_it->frequencia == 27.0) {
                it->second.erase(simbolo_it);  // Remove o 'R'
                return true;  // Indica que foi removido
            }
        }
    }
    return false;  // 'R' não foi removido
}

// Implementações para K4
bool GerenciadorContextos::adicionarSimboloK4(string& contexto, char simbolo) {
    auto it = tabelaContextosK4.find(contexto);
    if (it != tabelaContextosK4.end()) {
        for (auto& s : it->second) {
            if (s.representacao == simbolo) return false;
        }
        it->second.push_back({simbolo, 1.0});
        return true;
    }
    return false;
}

bool GerenciadorContextos::incrementarFrequenciaK4(string& contexto, char simbolo) {
    auto it = tabelaContextosK4.find(contexto);
    if (it != tabelaContextosK4.end()) {
        for (auto& s : it->second) {
            if (s.representacao == simbolo) {
                s.frequencia += 1.0;
                return true;
            }
        }
    }
    return false;
}

void GerenciadorContextos::ordenarPorFrequenciaK4(string& contexto) {
    auto it = tabelaContextosK4.find(contexto);
    if (it != tabelaContextosK4.end()) {
        sort(it->second.begin(), it->second.end());
    }
}

bool GerenciadorContextos::verificarSeSimboloExisteK4(string& contexto, char simbolo){
    // Verifica se o contexto existe
    auto it = tabelaContextosK4.find(contexto);
    if (it != tabelaContextosK4.end()) {
        // Percorre todos os símbolos do contexto
        for (const auto& s : it->second) {
            // Retorna true se encontrar uma representação igual
            if (s.representacao == simbolo) {
                return true;
            }
        }
    }
    return false; // Não encontrou o símbolo ou o contexto não existe
}

vector<double> GerenciadorContextos::getFrequenciasOrdenadasExcluidasK4(string& contexto) {
    vector<double> frequencias;
    auto it = tabelaContextosK4.find(contexto);
    
    if (it != tabelaContextosK4.end()) {
        // Faz uma cópia para ordenar sem modificar o original
        vector<Simbolo> copia = it->second;
        sort(copia.begin(), copia.end());
        
        for (const auto& simbolo : copia) {
            // Verifica se o símbolo não está na lista de exclusão
            if (simbolosParaExclusao.find(simbolo.representacao) == string::npos) {
                frequencias.push_back(simbolo.frequencia);
            }
        }
    }
    
    return frequencias;
}

int GerenciadorContextos::getPosicaoOrdenadaExcluidosK4(string& contexto, char simbolo) {
    auto it = tabelaContextosK4.find(contexto);
    if (it != tabelaContextosK4.end()) {
        // Cria cópia filtrada e ordenada
        vector<Simbolo> filtrados;
        for (const auto& s : it->second) {
            if (simbolosParaExclusao.find(s.representacao) == string::npos) {
                filtrados.push_back(s);
            }
        }
        sort(filtrados.begin(), filtrados.end());
        
        // Busca a posição do símbolo
        for (int i = 0; i < filtrados.size(); ++i) {
            if (filtrados[i].representacao == simbolo) {
                return i; // Retorna a posição (0-based)
            }
        }
    }
    return -1; // Não encontrado ou contexto inexistente
}

string GerenciadorContextos::getTodosSimbolosK4(string& contexto) {
    string simbolos;
    auto it = tabelaContextosK4.find(contexto);
    
    if (it != tabelaContextosK4.end()) {
        for (const auto& s : it->second) {
            // Exclui 'R' e quaisquer símbolos em simbolosParaExclusao
            if (s.representacao != 'R' && 
                simbolosParaExclusao.find(s.representacao) == string::npos) {
                simbolos += s.representacao;
            }
        }
    }
    return simbolos;
}

bool GerenciadorContextos::verificarERemoverRSeNecessarioK4(string& contexto) {
    auto it = tabelaContextosK4.find(contexto);
    if (it != tabelaContextosK4.end()) {
        // Procura pelo símbolo 'R' no vetor
        for (auto simbolo_it = it->second.begin(); simbolo_it != it->second.end(); ++simbolo_it) {
            if (simbolo_it->representacao == 'R' && simbolo_it->frequencia == 27.0) {
                it->second.erase(simbolo_it);  // Remove o 'R'
                return true;  // Indica que foi removido
            }
        }
    }
    return false;  // 'R' não foi removido
}

// Implementações para K5
bool GerenciadorContextos::adicionarSimboloK5(string& contexto, char simbolo) {
    auto it = tabelaContextosK5.find(contexto);
    if (it != tabelaContextosK5.end()) {
        for (auto& s : it->second) {
            if (s.representacao == simbolo) return false;
        }
        it->second.push_back({simbolo, 1.0});
        return true;
    }
    return false;
}

bool GerenciadorContextos::incrementarFrequenciaK5(string& contexto, char simbolo) {
    auto it = tabelaContextosK5.find(contexto);
    if (it != tabelaContextosK5.end()) {
        for (auto& s : it->second) {
            if (s.representacao == simbolo) {
                s.frequencia += 1.0;
                return true;
            }
        }
    }
    return false;
}

void GerenciadorContextos::ordenarPorFrequenciaK5(string& contexto) {
    auto it = tabelaContextosK5.find(contexto);
    if (it != tabelaContextosK5.end()) {
        sort(it->second.begin(), it->second.end());
    }
}

bool GerenciadorContextos::verificarSeSimboloExisteK5(string& contexto, char simbolo){
    // Verifica se o contexto existe
    auto it = tabelaContextosK5.find(contexto);
    if (it != tabelaContextosK5.end()) {
        // Percorre todos os símbolos do contexto
        for (const auto& s : it->second) {
            // Retorna true se encontrar uma representação igual
            if (s.representacao == simbolo) {
                return true;
            }
        }
    }
    return false; // Não encontrou o símbolo ou o contexto não existe
}

vector<double> GerenciadorContextos::getFrequenciasOrdenadasExcluidasK5(string& contexto) {
    vector<double> frequencias;
    auto it = tabelaContextosK5.find(contexto);
    
    if (it != tabelaContextosK5.end()) {
        // Faz uma cópia para ordenar sem modificar o original
        vector<Simbolo> copia = it->second;
        sort(copia.begin(), copia.end());
        
        for (const auto& simbolo : copia) {
            // Verifica se o símbolo não está na lista de exclusão
            if (simbolosParaExclusao.find(simbolo.representacao) == string::npos) {
                frequencias.push_back(simbolo.frequencia);
            }
        }
    }
    
    return frequencias;
}

int GerenciadorContextos::getPosicaoOrdenadaExcluidosK5(string& contexto, char simbolo) {
    auto it = tabelaContextosK5.find(contexto);
    if (it != tabelaContextosK5.end()) {
        // Cria cópia filtrada e ordenada
        vector<Simbolo> filtrados;
        for (const auto& s : it->second) {
            if (simbolosParaExclusao.find(s.representacao) == string::npos) {
                filtrados.push_back(s);
            }
        }
        sort(filtrados.begin(), filtrados.end());
        
        // Busca a posição do símbolo
        for (int i = 0; i < filtrados.size(); ++i) {
            if (filtrados[i].representacao == simbolo) {
                return i; // Retorna a posição (0-based)
            }
        }
    }
    return -1; // Não encontrado ou contexto inexistente
}

string GerenciadorContextos::getTodosSimbolosK5(string& contexto) {
    string simbolos;
    auto it = tabelaContextosK5.find(contexto);
    
    if (it != tabelaContextosK5.end()) {
        for (const auto& s : it->second) {
            // Exclui 'R' e quaisquer símbolos em simbolosParaExclusao
            if (s.representacao != 'R' && 
                simbolosParaExclusao.find(s.representacao) == string::npos) {
                simbolos += s.representacao;
            }
        }
    }
    return simbolos;
}

bool GerenciadorContextos::verificarERemoverRSeNecessarioK5(string& contexto) {
    auto it = tabelaContextosK5.find(contexto);
    if (it != tabelaContextosK5.end()) {
        // Procura pelo símbolo 'R' no vetor
        for (auto simbolo_it = it->second.begin(); simbolo_it != it->second.end(); ++simbolo_it) {
            if (simbolo_it->representacao == 'R' && simbolo_it->frequencia == 27.0) {
                it->second.erase(simbolo_it);  // Remove o 'R'
                return true;  // Indica que foi removido
            }
        }
    }
    return false;  // 'R' não foi removido
}

string GerenciadorContextos::gerarCodigoK5(string& contexto, char simboloDesejado){
    string codigoGerado = "";
    zerarSimbolosParaExclusao();

    if(verificarCriarK5(contexto)){
        if(verificarSeSimboloExisteK5(contexto, simboloDesejado)){      
            auto frequenciasOrdenadas = getFrequenciasOrdenadasExcluidasK5(contexto);
            codigoGerado +=  obterCodigoHuffman(frequenciasOrdenadas, getPosicaoOrdenadaExcluidosK5(contexto, simboloDesejado));
            atualizarContextos(contexto, simboloDesejado);
            return codigoGerado;
        }else{
            //caso seja RO
            auto frequenciasOrdenadas = getFrequenciasOrdenadasExcluidasK5(contexto);
            codigoGerado +=  obterCodigoHuffman(frequenciasOrdenadas, getPosicaoOrdenadaExcluidosK5(contexto, 'R'));
            adicionarSimboloK5(contexto, simboloDesejado);
            incrementarFrequenciaK5(contexto, 'R');
            simbolosParaExclusao += getTodosSimbolosK5(contexto);
            verificarERemoverRSeNecessarioK5(contexto);

        }
    }
    contexto = contexto.substr(contexto.size() - 4, 4);

    if(verificarCriarK4(contexto)){
        if(verificarSeSimboloExisteK4(contexto, simboloDesejado)){    
            auto frequenciasOrdenadas = getFrequenciasOrdenadasExcluidasK4(contexto);
            codigoGerado +=  obterCodigoHuffman(frequenciasOrdenadas, getPosicaoOrdenadaExcluidosK4(contexto, simboloDesejado));
            atualizarContextos(contexto, simboloDesejado);
            return codigoGerado;
        }else{
            //caso seja RO
            auto frequenciasOrdenadas = getFrequenciasOrdenadasExcluidasK4(contexto);
            codigoGerado +=  obterCodigoHuffman(frequenciasOrdenadas, getPosicaoOrdenadaExcluidosK4(contexto, 'R'));
            adicionarSimboloK4(contexto, simboloDesejado);
            incrementarFrequenciaK4(contexto, 'R');
            simbolosParaExclusao += getTodosSimbolosK4(contexto);
            verificarERemoverRSeNecessarioK4(contexto);

        }
    }
    contexto = contexto.substr(contexto.size() - 3, 3);

    if(verificarCriarK3(contexto)){
        if(verificarSeSimboloExisteK3(contexto, simboloDesejado)){  
            auto frequenciasOrdenadas = getFrequenciasOrdenadasExcluidasK3(contexto);
            codigoGerado += obterCodigoHuffman(frequenciasOrdenadas, getPosicaoOrdenadaExcluidosK3(contexto, simboloDesejado));
            atualizarContextos(contexto, simboloDesejado);
            return codigoGerado;
        }else{
            //caso seja RO
            auto frequenciasOrdenadas = getFrequenciasOrdenadasExcluidasK3(contexto);
            codigoGerado += obterCodigoHuffman(frequenciasOrdenadas, getPosicaoOrdenadaExcluidosK3(contexto, 'R'));
            adicionarSimboloK3(contexto, simboloDesejado);
            incrementarFrequenciaK3(contexto, 'R');
            simbolosParaExclusao += getTodosSimbolosK3(contexto);
            verificarERemoverRSeNecessarioK3(contexto);

        }
    }
    contexto = contexto.substr(contexto.size() - 2, 2);

    if(verificarCriarK2(contexto)){
        if(verificarSeSimboloExisteK2(contexto, simboloDesejado)){    
            auto frequenciasOrdenadas = getFrequenciasOrdenadasExcluidasK2(contexto);
            codigoGerado += obterCodigoHuffman(frequenciasOrdenadas, getPosicaoOrdenadaExcluidosK2(contexto, simboloDesejado));
            atualizarContextos(contexto, simboloDesejado);
            return codigoGerado;
        }else{
            //caso seja RO
            auto frequenciasOrdenadas = getFrequenciasOrdenadasExcluidasK2(contexto);
            codigoGerado +=  obterCodigoHuffman(frequenciasOrdenadas, getPosicaoOrdenadaExcluidosK2(contexto, 'R'));
            adicionarSimboloK2(contexto, simboloDesejado);
            incrementarFrequenciaK2(contexto, 'R');
            simbolosParaExclusao += getTodosSimbolosK2(contexto);
            verificarERemoverRSeNecessarioK2(contexto);

        }
    }
    contexto = contexto.substr(contexto.size() - 1, 1);

    if(verificarCriarK1(contexto)){
        
        if(verificarSeSimboloExisteK1(contexto, simboloDesejado)){
            auto frequenciasOrdenadas = getFrequenciasOrdenadasExcluidasK1(contexto);
            codigoGerado +=  obterCodigoHuffman(frequenciasOrdenadas, getPosicaoOrdenadaExcluidosK1(contexto, simboloDesejado));
            atualizarContextos(contexto, simboloDesejado);
            return codigoGerado;
        }else{
            
            //caso seja RO
            auto frequenciasOrdenadas = getFrequenciasOrdenadasExcluidasK1(contexto);

            

            codigoGerado += obterCodigoHuffman(frequenciasOrdenadas, getPosicaoOrdenadaExcluidosK1(contexto, 'R'));
            adicionarSimboloK1(contexto, simboloDesejado);
            incrementarFrequenciaK1(contexto, 'R');
            simbolosParaExclusao += getTodosSimbolosK1(contexto);
            verificarERemoverRSeNecessarioK1(contexto);
        }
    }
    
    codigoGerado +=gerarCodigoK0(simboloDesejado);
    
    return codigoGerado;
}



void GerenciadorContextos::setSimbolosParaExclusao(string& simbolos) {
    simbolosParaExclusao += simbolos;
}

void GerenciadorContextos::zerarSimbolosParaExclusao() {
    simbolosParaExclusao = "";
}

void GerenciadorContextos::atualizarContextos(string& contexto, char simboloDesejado){
    int i = contexto.size();
        
        if(i==5){
            incrementarFrequenciaK5(contexto, simboloDesejado);
            ordenarPorFrequenciaK5(contexto);
            i--;
        }
        if(i==4){
            contexto = contexto.substr(contexto.size() - i, i);
            incrementarFrequenciaK4(contexto, simboloDesejado);
            ordenarPorFrequenciaK4(contexto);
            i--;
        }
        if(i==3){  
            contexto = contexto.substr(contexto.size() - i, i);
            incrementarFrequenciaK3(contexto, simboloDesejado);
            ordenarPorFrequenciaK3(contexto);
            i--;
        }
        if(i==2){
            contexto = contexto.substr(contexto.size() - i, i);
            incrementarFrequenciaK2(contexto, simboloDesejado);
            ordenarPorFrequenciaK2(contexto);
            i--;
        }
        if(i==1){
            contexto = contexto.substr(contexto.size() - i, i);
            incrementarFrequenciaK1(contexto, simboloDesejado);
            ordenarPorFrequenciaK1(contexto);
        }
    incrementarFrequenciaK0(simboloDesejado);
    
}

int main() {
    GerenciadorContextos gerenciador;
    

    LeitorDeArquivo leitor("saida.txt");
    conversor conversorK5("saida.bin");

    double total_de_bits = 0;
    double total_de_caracteres = 0;
    high_resolution_clock::time_point inicio = high_resolution_clock::now();
    
    leitor.atualizarLetras();

    while(leitor.temMaisLetras()){
        string contexto = leitor.getContexto(5);
        char ultimaLetra = leitor.getUltimasSaidas();
        string codigo = gerenciador.gerarCodigoK5(contexto, ultimaLetra);
        total_de_bits += codigo.size();
        leitor.atualizarLetras();
        conversorK5.adicionarcodigo(codigo);
        total_de_caracteres++;
    }

    conversorK5.fechararquivo();
    double comprimento_medio = total_de_bits / total_de_caracteres;


    high_resolution_clock::time_point fim = high_resolution_clock::now();

    auto duracao_ns = duration_cast<nanoseconds>(fim - inicio).count();
    double duracao_segundos = duracao_ns / 1'000'000'000.0;
    cout << "Tempo de compressão: " << duracao_segundos << " s" << endl;
    cout << "Comprimento médio do código: " << comprimento_medio << " bits/simbolo" << endl; 

 char c;
 cin >> c;
    return 0;
}

/*
// Função stub: decodifica um símbolo com base nas frequências fornecidas.
// Ela deve ler do fluxo de bits (bitstream) a partir da posição bitPos e retornar o índice decodificado.
// bitPos é atualizado com a quantidade de bits lidos.
int decodificarHuffman(const vector<double>& frequencias, const string& bitstream, int &bitPos) {
    // Aqui você deverá implementar o decodificador Huffman inverso.
    // Uma possibilidade é reconstruir a árvore de Huffman com base no vetor "frequencias"
    // e, a partir de bitPos, percorrer a árvore conforme os bits até encontrar uma folha.
    // Por simplicidade, este stub retorna 0.
    // ---
    // Exemplo:
    // HuffmanTree tree = construirArvoreHuffman(frequencias);
    // int indice = tree.decodificar(bitstream, bitPos);
    // return indice;
    return 0; // <-- Implementar corretamente!
}

// Função que decodifica um símbolo utilizando a hierarquia de contextos (K5 a K0)
// com base no fluxo de bits. A função atualiza os modelos de contextos à medida que decodifica.
char decodificarSimbolo(GerenciadorContextos& gerenciador, string& contexto, const string& bitstream, int& bitPos) {
    char simboloDecodificado = '\0';
    bool simboloEncontrado = false;
    string codigo; // pode ser utilizado para debug ou validação

    // Tenta decodificar nos níveis de contexto do mais específico (K5) para o menos específico (K0)
    // Cada nível tenta decodificar o símbolo a partir da tabela de frequências atual.
    // Se o símbolo decodificado for diferente de 'R', então ele é o símbolo desejado;
    // caso contrário, trata-se do código de escape e passamos para o próximo nível.

    // Nível K5 (contexto com 5 caracteres)
    if (contexto.size() >= 5) {
        string ctxK5 = contexto.substr(contexto.size() - 5, 5);
        if (gerenciador.verificarCriarK5(ctxK5)) {
            vector<double> freqK5 = gerenciador.getFrequenciasOrdenadasExcluidasK5(ctxK5);
            int indice = decodificarHuffman(freqK5, bitstream, bitPos);
            // A função getPosicaoOrdenadaExcluidosK5 foi usada na compressão para obter o índice.
            // Agora, precisamos identificar qual símbolo corresponde a esse índice.
            // Supondo que você tenha uma função auxiliar que, dada a lista de símbolos (ou a string retornada por getTodosSimbolosK5)
            // e o índice, retorne o símbolo correspondente.
            string simbolosK5 = gerenciador.getTodosSimbolosK5(ctxK5);
            // Se o índice decodificado apontar para 'R', trata-se de escape (RO)
            if (indice >= 0 && indice < (int)simbolosK5.size() && simbolosK5[indice] != 'R') {
                simboloDecodificado = simbolosK5[indice];
                gerenciador.atualizarContextos(ctxK5, simboloDecodificado);
                simboloEncontrado = true;
                return simboloDecodificado;
            }
            // Caso contrário, é o código de escape – o modelo é atualizado conforme na compressão.
            // Nesse caso, execute as operações de escape:
            // (Lembre-se que na compressão, após o código de escape, não foi retornado o símbolo,
            //  e o fluxo prossegue para o próximo nível.)
            // Aqui, você deverá simular as mesmas atualizações, por exemplo:
            // - Ler o código de escape (já decodificado como índice de 'R')
            // - Atualizar o modelo (adicionar símbolo, incrementar frequência de 'R', etc.)
            // – e então seguir para o próximo nível (K4).
            // Para simplificar, vamos assumir que nesse caso apenas avançamos para o próximo nível.
        }
    }

    // Nível K4 (contexto com 4 caracteres)
    if (!simboloEncontrado && contexto.size() >= 4) {
        string ctxK4 = contexto.substr(contexto.size() - 4, 4);
        if (gerenciador.verificarCriarK4(ctxK4)) {
            vector<double> freqK4 = gerenciador.getFrequenciasOrdenadasExcluidasK4(ctxK4);
            int indice = decodificarHuffman(freqK4, bitstream, bitPos);
            string simbolosK4 = gerenciador.getTodosSimbolosK4(ctxK4);
            if (indice >= 0 && indice < (int)simbolosK4.size() && simbolosK4[indice] != 'R') {
                simboloDecodificado = simbolosK4[indice];
                gerenciador.atualizarContextos(ctxK4, simboloDecodificado);
                simboloEncontrado = true;
                return simboloDecodificado;
            }
            // Se for 'R', trata-se de escape – atualize o modelo e continue para o nível K3.
        }
    }

    // Nível K3 (contexto com 3 caracteres)
    if (!simboloEncontrado && contexto.size() >= 3) {
        string ctxK3 = contexto.substr(contexto.size() - 3, 3);
        if (gerenciador.verificarCriarK3(ctxK3)) {
            vector<double> freqK3 = gerenciador.getFrequenciasOrdenadasExcluidasK3(ctxK3);
            int indice = decodificarHuffman(freqK3, bitstream, bitPos);
            string simbolosK3 = gerenciador.getTodosSimbolosK3(ctxK3);
            if (indice >= 0 && indice < (int)simbolosK3.size() && simbolosK3[indice] != 'R') {
                simboloDecodificado = simbolosK3[indice];
                gerenciador.atualizarContextos(ctxK3, simboloDecodificado);
                simboloEncontrado = true;
                return simboloDecodificado;
            }
        }
    }

    // Nível K2 (contexto com 2 caracteres)
    if (!simboloEncontrado && contexto.size() >= 2) {
        string ctxK2 = contexto.substr(contexto.size() - 2, 2);
        if (gerenciador.verificarCriarK2(ctxK2)) {
            vector<double> freqK2 = gerenciador.getFrequenciasOrdenadasExcluidasK2(ctxK2);
            int indice = decodificarHuffman(freqK2, bitstream, bitPos);
            string simbolosK2 = gerenciador.getTodosSimbolosK2(ctxK2);
            if (indice >= 0 && indice < (int)simbolosK2.size() && simbolosK2[indice] != 'R') {
                simboloDecodificado = simbolosK2[indice];
                gerenciador.atualizarContextos(ctxK2, simboloDecodificado);
                simboloEncontrado = true;
                return simboloDecodificado;
            }
        }
    }

    // Nível K1 (contexto com 1 caractere)
    if (!simboloEncontrado && contexto.size() >= 1) {
        string ctxK1 = contexto.substr(contexto.size() - 1, 1);
        if (gerenciador.verificarCriarK1(ctxK1)) {
            vector<double> freqK1 = gerenciador.getFrequenciasOrdenadasExcluidasK1(ctxK1);
            int indice = decodificarHuffman(freqK1, bitstream, bitPos);
            string simbolosK1 = gerenciador.getTodosSimbolosK1(ctxK1);
            if (indice >= 0 && indice < (int)simbolosK1.size() && simbolosK1[indice] != 'R') {
                simboloDecodificado = simbolosK1[indice];
                gerenciador.atualizarContextos(ctxK1, simboloDecodificado);
                simboloEncontrado = true;
                return simboloDecodificado;
            }
        }
    }

    // Se não foi encontrado em nenhum dos níveis, chega-se ao K0.
    // Aqui o procedimento é:
    // 1. Decodificar usando o modelo K0.
    // 2. Se o símbolo decodificado for 'R', significa que é um novo símbolo,
    //    e então é necessário ler bits adicionais para obter o caractere “nunca visto”.
    // 3. Atualiza o modelo K0.
    {
        // Para K0, use o mesmo procedimento:
        vector<double> freqK0 = gerenciador.getFrequenciasOrdenadasExcluidasK0();  // supondo que haja uma função similar para K0
        int indice = decodificarHuffman(freqK0, bitstream, bitPos);
        // Suponha que tenhamos uma função que retorne o símbolo com base no índice no vetor K0
        char simboloK0 = gerenciador.getSimboloK0PorPosicao(indice); // função hipotética
        if (simboloK0 != 'R') {
            simboloDecodificado = simboloK0;
            gerenciador.incrementarFrequenciaK0(simboloDecodificado);
        } else {
            // Se for 'R', decodifica o código do símbolo "nunca visto".
            // A lógica da compressão usava: codigo += contextoMenos1.getCodigoNuncaVisto(simboloDesejado);
            // Aqui você deve implementar a leitura dos bits correspondentes a esse novo símbolo.
            // Exemplo (a ser implementado conforme sua lógica):
            char novoSimbolo;
            // novoSimbolo = decodificarNuncaVisto(bitstream, bitPos);
            simboloDecodificado = novoSimbolo;
            // Após decodificar o novo símbolo, atualize o modelo K0 com a adição dele.
            gerenciador.adicionarSimboloK0(novoSimbolo);
        }
    }

    return simboloDecodificado;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Uso: descompressor <arquivo_comprimido> <arquivo_saida>" << endl;
        return 1;
    }

    // Abrir arquivos de entrada e saída
    ifstream arquivoEntrada(argv[1], ios::binary);
    if (!arquivoEntrada) {
        cerr << "Erro ao abrir arquivo de entrada." << endl;
        return 1;
    }
    ofstream arquivoSaida(argv[2], ios::binary);
    if (!arquivoSaida) {
        cerr << "Erro ao abrir arquivo de saída." << endl;
        return 1;
    }

    // Ler o conteúdo do arquivo comprimido em uma string (representação binária)
    // Aqui, assumimos que o arquivo contém uma sequência de '0' e '1'.
    // Se for um fluxo binário, você precisará convertê-lo para uma string de bits.
    string bitstream((istreambuf_iterator<char>(arquivoEntrada)), istreambuf_iterator<char>());
    int posBit = 0;

    GerenciadorContextos gerenciador;
    string contexto = "";  // Inicialmente, o contexto pode estar vazio ou com algum valor fixo

    // Enquanto houver bits para ler, decodifica símbolo a símbolo.
    while (posBit < (int)bitstream.size()) {
        char simbolo = decodificarSimbolo(gerenciador, contexto, bitstream, posBit);
        // Se o símbolo decodificado for um caractere nulo ou se chegar ao fim,
        // você pode considerar terminar a descompressão.
        if (simbolo == '\0')
            break;

        arquivoSaida.put(simbolo);
        contexto.push_back(simbolo);
        // Limita o tamanho do contexto (por exemplo, 5 caracteres)
        if (contexto.size() > 5) {
            contexto = contexto.substr(contexto.size() - 5, 5);
        }
    }

    arquivoEntrada.close();
    arquivoSaida.close();
    cout << "Descompressão finalizada." << endl;
    return 0;
}
*/