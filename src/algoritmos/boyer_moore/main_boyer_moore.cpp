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
    int cant_documentos = 5;
    vector<document> docs = cargarDocumentos(ruta_documentos, cant_documentos);
    vector<string> patrones = cargarPatrones(ruta_patron);

    for(auto& patron : patrones){
        for(auto& doc : docs) {
            auto start = chrono::high_resolution_clock::now();
            int freq = searchBM(doc.text, patron);
            auto end = chrono::high_resolution_clock::now();
            double running_time = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
            running_time *= 1e-9; // Convertir a segundos
            cout << "./booyer_moore_"<< cant_documentos << ";" << patrones.size()<< ";"<< freq << ";" << running_time << endl;
        }
    }

    return 0;
}
