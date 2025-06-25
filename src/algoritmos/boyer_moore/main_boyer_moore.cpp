#include "boyer_moore.h"
#include "../../leer_archivos.h"
#include <iostream>
#include <chrono>

// Compilacion: 
// g++ -std=c++17 -o boyer_moore main_boyer_moore.cpp boyer_moore.cpp ../../leer_archivos.cpp -I../../
// ./boyer_moore

int main(int argc,  char** argv) {
    if(argc < 2) 
        cerr << "Uso: " << argv[0] << " <ruta a patron> " << endl;  
    
    string ruta_documentos = "../datos_de_pruebas/documentos";
    string ruta_patron = argv[1];
    // cout << "Ingrese ruta del dataset particionado: ";
    // getline(cin, ruta_documentos);

    // cout << "Ingrese ruta del set de patrones: ";
    // getline(cin, ruta_patron);

    vector<document> docs = load_documents(ruta_documentos, 10);
    vector<string> patrones = cargarPatrones(ruta_patron);

    for(auto& patron : patrones){
        //cout<< "El patron a probar es: " << patron<<endl;
        for(auto& doc : docs) {
            auto start = chrono::high_resolution_clock::now();
            int freq = searchBM(doc.text, patron);
            auto end = chrono::high_resolution_clock::now();
            double running_time = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
            running_time *= 1e-9; // Convertir a segundos
            cout << argv[0] << ";" << patrones.size()<< ";"<< freq << ";" << running_time << endl;
            //cout << "Archivo: " << doc.name << " -> " << freq << " ocurrencias.\n";
        }
    }
    return 0;
}
