#include "boyer_moore.h"
#include "../../leer_archivos.h"
#include <iostream>
#include <chrono>

// Compilacion: 
// g++ -std=c++17 -o boyer_moore main_boyer_moore.cpp boyer_moore.cpp ../../leer_archivos.cpp -I../../
// ./boyer_moore

int main() {
    string ruta_documentos;
    string ruta_patron;
    cout << "Ingrese ruta del dataset particionado: ";
    getline(cin, ruta_documentos);

    cout << "Ingrese ruta del set de patrones: ";
    getline(cin, ruta_patron);

    vector<document> docs = load_documents(ruta_documentos, 10);
    vector<string> patrones = cargarPatrones(ruta_patron);

    for(auto& patron : patrones){
        cout<< "El patron a probar es: " << patron<<endl;
        for(auto& doc : docs) {
            int freq = searchBM(doc.text, patron);
            cout << "Archivo: " << doc.name << " -> " << freq << " ocurrencias.\n";
        }
    }
    return 0;
}
