#include "Knuth-Morris-Pratt.h"
#include "../../leer_archivos.h"
#include <iostream>
#include <chrono>

// Compilacion: 
// g++ -std=c++17 -o kmp main_kmp.cpp Knuth-Morris-Pratt.cpp ../../leer_archivos.cpp -I../../
// ./kmp

int main(int argc,  char** argv) {
    if(argc < 3) 
        cerr << "Uso: " << argv[0] << " <ruta a patron> <numero de archivos>" << endl;  
    
    //string ruta_documentos = "../../../datos_de_pruebas/documentos"; //ruta si se ejecuta en este directorio
    string ruta_documentos = "../datos_de_pruebas/documentos"; //ruta si se ejecuta desde los tests
    string ruta_patron = argv[1];
    int num_docs = stoi(argv[2]);

    vector<document> docs = load_documents(ruta_documentos, num_docs);
    vector<string> patrones = cargarPatrones(ruta_patron);

    auto start = chrono::high_resolution_clock::now();
    for(auto& patron : patrones){
        //cout<< "El patron a probar es: " << patron<<endl;
        for(auto& doc : docs) {
            //auto start = chrono::high_resolution_clock::now();
            int freq = KMP(doc.text, patron);
            //auto end = chrono::high_resolution_clock::now();
            //double running_time = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
            //running_time *= 1e-9; // Convertir a segundos
            //cout << argv[0] << ";" << patrones.size()<< ";"<< freq << ";" << running_time << endl;
          
        }
    }
    auto end = chrono::high_resolution_clock::now();
    double running_time = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    running_time *= 1e-9; // Convertir a segundos
    cout << argv[0] << ";" << patrones.size()<< ";" <<num_docs<< ";" <<running_time << endl;
    return 0;
}