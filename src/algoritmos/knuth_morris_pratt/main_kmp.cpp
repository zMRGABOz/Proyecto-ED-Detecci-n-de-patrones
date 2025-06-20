#include "Knuth-Morris-Pratt.h"
#include "../../leer_archivos.h"
#include <iostream>
#include <chrono>

// Compilacion: 
// g++ -std=c++17 -o kmp main_kmp.cpp Knuth-Morris-Pratt.cpp ../../leer_archivos.cpp -I../../
// ./kmp

int main() {
    string ruta;
    string patron = "GATC";
    cout << "Ingrese ruta del dataset particionado: ";
    getline(cin, ruta);

    vector<document> docs = load_documents(ruta);

    for(auto& doc : docs) {
        int freq = searchBM(doc.text, patron);
        cout << "Archivo: " << doc.name << " -> " << freq << " ocurrencias.\n";
    }
    return 0;
}