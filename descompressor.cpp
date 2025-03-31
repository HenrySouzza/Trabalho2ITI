#include <iostream>
#include <fstream>
#include <string>
#include <bitset>
#include <vector>

using namespace std;

class Descompressor {
private:
    ifstream arquivoBinario;
    ofstream arquivoTexto;
    string bufferBits;

public:
    Descompressor(const string& arquivoEntrada, const string& arquivoSaida)
        : arquivoBinario(arquivoEntrada, ios::binary), arquivoTexto(arquivoSaida) {
        if (!arquivoBinario.is_open()) {
            throw runtime_error("Erro ao abrir arquivo binário para leitura");
        }
        if (!arquivoTexto.is_open()) {
            throw runtime_error("Erro ao abrir arquivo de texto para escrita");
        }
    }

    ~Descompressor() {
        if (arquivoBinario.is_open()) {
            arquivoBinario.close();
        }
        if (arquivoTexto.is_open()) {
            arquivoTexto.close();
        }
    }

    void descomprimir() {
        char byte;
        while (arquivoBinario.read(&byte, sizeof(byte))) {
            // Converte cada byte para 8 bits e adiciona ao buffer
            bitset<8> bits(byte);
            bufferBits += bits.to_string();
            
            // Processa os bits completos (múltiplos de 8) enquanto houver
            processarBuffer();
        }
        
        // Processa quaisquer bits restantes no buffer (último byte pode ter padding)
        if (!bufferBits.empty()) {
            // Remove o padding (zeros adicionados no final)
            size_t paddingPos = bufferBits.find_last_of('1');
            if (paddingPos != string::npos) {
                bufferBits = bufferBits.substr(0, paddingPos + 1);
            }
            processarBuffer();
        }
    }

private:
    void processarBuffer() {
        // Aqui você implementaria a lógica específica de descompressão
        // Por enquanto, apenas converte os bits de volta para caracteres ASCII
        // (Isso é um placeholder - você precisará adaptar para seu esquema de codificação real)
        
        // Processa em blocos de 8 bits
        while (bufferBits.length() >= 8) {
            string byteStr = bufferBits.substr(0, 8);
            bitset<8> bits(byteStr);
            char c = static_cast<char>(bits.to_ulong());
            arquivoTexto << c;
            bufferBits.erase(0, 8);
        }
    }
};

// int main() {
//     try {
//         Descompressor descompressor("saida.bin", "saidadescomprimida.txt");
//         descompressor.descomprimir();
//         cout << "Descompressão concluída com sucesso!" << endl;
//     } catch (const exception& e) {
//         cerr << "Erro: " << e.what() << endl;
//         return 1;
//     }
    
//     return 0;
// }