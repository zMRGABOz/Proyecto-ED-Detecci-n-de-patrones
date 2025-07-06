#include "Knuth-Morris-Pratt.h"
#include "../../leer_archivos.h"
#include <iostream>
#include <chrono>

// Compilacion: 
// g++ -std=c++17 -o kmp main_kmp.cpp Knuth-Morris-Pratt.cpp ../../leer_archivos.cpp -I../../

int main(int argc,  char** argv) {
    if(argc < 4) {
        cerr << "Uso: " << argv[0] << " <ruta a patron> <ruta documento> <numero de archivos>" << endl;  
        return 1;
    }
    string ruta_documentos = argv [2];
    string ruta_patron = argv[1];
    int num_docs = atoi(argv[3]);

    vector<document> docs = cargarDocumentos(ruta_documentos, num_docs);
    vector<string> patrones = cargarPatrones(ruta_patron);

    auto start = chrono::high_resolution_clock::now();
    for(auto& patron : patrones){
        for(auto& doc : docs) {
            int freq = KMP(doc.text, patron); 
        }
    }
    auto end = chrono::high_resolution_clock::now();
    double running_time = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    running_time *= 1e-9; // Convertir a segundos
    cout << "./knuth_morris_pratt" << ";" << patrones.size()<< ";" <<num_docs<< ";" <<running_time << endl;
    return 0;
}