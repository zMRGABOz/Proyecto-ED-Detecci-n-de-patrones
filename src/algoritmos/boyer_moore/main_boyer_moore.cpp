#include "boyer_moore.h"
// #include "../../leer_archivos.h"
#include <iostream>
#include <chrono>

// Compilacion: 
// g++ -std=c++17 -o boyer_moore main_boyer_moore.cpp boyer_moore.cpp ../../leer_archivos.cpp -I../../
// ./boyer_moore

int main() {
    // string ruta;
    // string pat = "ar";
    // cout << "Ingrese ruta del dataset particionado: ";
    // getline(cin, ruta);

    // vector<document> documentos = load_documents(ruta);

    // for(const document doc : documentos){
    //     cout << "ID: " << doc.id << " nombre: "<< doc.name << endl;
    // }
    string txt = "ABAAABCDABAA";
    string pat = "ABAA";
    int veces = searchBM(txt, pat);
    cout << veces << endl;
    return 0;
}
