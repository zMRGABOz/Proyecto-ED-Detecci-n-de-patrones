#include "SuffixArray.h"
#include <filesystem>
namespace fs = std::filesystem;

//g++ -o precomputar main_precomputar.cpp SuffixArrayPrefixDoubling.cpp ../leer_archivos.cpp

// Código para generar suffix arrays con prefix doubling precomputados
void Precomputar_suffix_arrays() {
    ofstream log_csv("tiempos_suffix_array.csv");
    log_csv << "tipo_documento;numDocs;tiempo(s)" << endl;

    vector<string> tipos_documento = {"DNA", "English", "Proteins", "Sources"};

    for (const string& tipo_documento : tipos_documento) {
        string ruta_documentos = "../../datos_de_pruebas/documentos/" + tipo_documento;

        for (int i = 5; i <= 40; i += 5) {
            vector<document> docs = cargarDocumentos(ruta_documentos, i);
            string texto_total = concatenar_textos(docs); // Se concatenan los documentos

            auto crear_sa_pd_start = chrono::high_resolution_clock::now();
            vector<int> suffix_array = build_suffix_array_preffix_doubling(texto_total);
            auto crear_sa_pd_end = chrono::high_resolution_clock::now();

            double crear_sa_pd_time = chrono::duration_cast<chrono::nanoseconds>(
                crear_sa_pd_end - crear_sa_pd_start
            ).count() * 1e-9;

            // Guardar en CSV
            log_csv << tipo_documento << ";" << i << ";" << crear_sa_pd_time << endl;

            // Guardar en archivo binario
            string nombre_archivo = "SA_PD_Precompilados/" + tipo_documento + "_" + to_string(i) + ".bin";
            ofstream archivo_bin(nombre_archivo, ios::binary);
            if (!archivo_bin) {
                cerr << "Error al abrir el archivo " << nombre_archivo << " para escritura.\n";
                continue;
            }

            int size = suffix_array.size();
            archivo_bin.write(reinterpret_cast<char*>(&size), sizeof(int));               // Cantidad de sufijos
            archivo_bin.write(reinterpret_cast<char*>(&crear_sa_pd_time), sizeof(double)); // Tiempo de creación
            archivo_bin.write(reinterpret_cast<char*>(suffix_array.data()), size * sizeof(int)); // Suffix array
            archivo_bin.close();
            cout << "Archivo creado: " << fs::absolute(nombre_archivo) << endl;
        }
    }

    log_csv.close();
}

int main(){
    Precomputar_suffix_arrays();
    return 0;
}
