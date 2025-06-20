#include "boyer_moore.h"
#include "../../leer_archivos.h"
#include <iostream>
#include <chrono>

// Compilacion: 
// g++ -std=c++17 -o boyer_moore main_boyer_moore.cpp boyer_moore.cpp ../../leer_archivos.cpp -I../../
// ./boyer_moore

int main() {
    string ruta;
    string patron = "GATC";
    cout << "Ingrese ruta del dataset particionado: ";
    getline(cin, ruta);

    vector<document> docs = load_documents(ruta, 10);

    for(auto& doc : docs) {
        int freq = searchBM(doc.text, patron);
        cout << "Archivo: " << doc.name << " -> " << freq << " ocurrencias.\n";
    }
    return 0;
}
