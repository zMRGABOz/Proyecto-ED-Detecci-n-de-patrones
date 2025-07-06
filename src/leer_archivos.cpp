/**
 * Funcion donada por Oliver Peñailillo. 
 * Gracias a Oliver y su grupo por ayudarnos con esta función. 
 * Obtenida de: https://github.com/Sephir0ath/file-pattern-analyzer 
 */
#include "leer_archivos.h"
#include <iostream>
#include <filesystem>
#include <fstream>
#include <sstream>

vector<document> cargarDocumentos(const string& directory_path, int num_files) {
    vector<document> documents;
    int current_index = 0;
    int id_counter = 0;
    int files_read = 0; 

    // -> lectura de archivos en el directorio
    for(const auto& file : filesystem::directory_iterator(directory_path)) {
        if (files_read >= num_files) break;

        if(file.is_regular_file()) {
            ifstream infile(file.path());
            if(!infile.is_open()) {
                cerr << "Error al abrir el documento: " << file.path() << endl;
                continue;
            }

            stringstream buffer;
            buffer << infile.rdbuf(); // -> lectura contenido del archivo
            string content = buffer.str();

            // -> creación documento y adición al vector
            document doc;
            doc.id = id_counter++; // -> id del documento (posición en directorio)
            doc.name = file.path().filename().string(); // -> nombre del archivo
            doc.text = content; // -> texto del documento
            doc.start_index = current_index; // -> índice de inicio en el texto concatenado
            doc.end_index = current_index + content.size() - 1;

            current_index += content.size() + 1; // -> actualizar índice para siguiente documento

            documents.push_back(doc);

            files_read++;
        }
    }

    return documents;
}

vector<string> cargarPatrones(const string& ruta_patron) {
    vector<string> patrones;
    ifstream archivo(ruta_patron);
    string linea;

    while (std::getline(archivo, linea)) {
        if (!linea.empty())
            patrones.push_back(linea);
    }
    return patrones;
}