#ifndef LEER_ARCHIVOS_H
#define LEER_ARCHIVOS_H
#include <vector>
#include <string>

using namespace std; 

struct document {
    int id; // -> identificador del documento (posición en directorio)
    string text; // -> texto del documento
    string name; // -> nombre del documento

    int start_index; // -> índice de inicio del documento en el texto concatenado
    int end_index; // -> índice de fin del documento en el texto concatenado
};

/**
 * @brief función para cargar documentos y su contenido desde un directorio
 * 
 * @param directory_path ruta hacia el directorio
 * @param num_files cantidad de archivos a leer
 */
vector<document> cargarDocumentos(const string& directory_path, int num_files);

/**
*
* @param ruta_patron ruta en donde se encuentran los patrones a probar
*/
vector<string> cargarPatrones(const string& ruta_patron);

#endif