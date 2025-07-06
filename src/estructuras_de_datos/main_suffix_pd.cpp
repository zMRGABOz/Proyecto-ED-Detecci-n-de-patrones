#include "SuffixArray.h"
#include <filesystem>
namespace fs = std::filesystem;

// g++ main_suffix_pd.cpp SuffixArrayPrefixDoubling.cpp ../leer_archivos.cpp -o SuffixArrayPrefixDoubling

//codigo para evaluar patrones con suffix arrays precomputados
int main(int argc, char** argv) {

    if (argc < 4) {
        cerr << "Uso: " << argv[0] << " <ruta a archivo de patrones; > <ruta documento> <numero de archivos>" << endl;
        return 1;
    }

    string ruta_patrones = argv[1];
    int cant_documentos = atoi(argv[3]);
    string ruta_documentos_base = argv[2]; //cambiar para probar con otros arhivos
    fs::path p(ruta_documentos_base);
    string tipo_documento = p.filename().string(); // Tipo de dataset: DNA, English, Proteins, Sources
    
    vector<string> patrones = cargarPatrones(ruta_patrones);


    // Cargar SA desde archivo binario
    string nombre_archivo = "../../src/estructuras_de_datos/SA_PD_Precompilados/" + tipo_documento + "_" + to_string(cant_documentos) + ".bin";
    ifstream archivo_bin(nombre_archivo, ios::binary);
    if (!archivo_bin) {
        cerr << "Error al abrir el archivo binario: " << nombre_archivo << endl;
    }

    int size = 0;
    double tiempo_creacion = 0;
    archivo_bin.read(reinterpret_cast<char*>(&size), sizeof(int));
    archivo_bin.read(reinterpret_cast<char*>(&tiempo_creacion), sizeof(double));

    vector<int> suffix_array(size);
    archivo_bin.read(reinterpret_cast<char*>(suffix_array.data()), size * sizeof(int));
    archivo_bin.close();

    // Cargar documentos y concatenar texto
    vector<document> docs = cargarDocumentos(ruta_documentos_base, cant_documentos);
    vector<int> largos_textos;
    int acumulado = 0;
    for (const auto& d : docs) {
        acumulado += d.text.length() + 1; // +1 por '$'
        largos_textos.push_back(acumulado);
    }

    string texto_total = concatenar_textos(docs);

    //tiempo de busqueda todos los patrones
    auto start = chrono::high_resolution_clock::now();
    // Buscar todos los patrones
    for (const string& patron : patrones) {
        map<int, int> resultados = contar_ocurrencias_por_texto(
            texto_total, suffix_array, patron, largos_textos
        );
    }
    
    auto end = chrono::high_resolution_clock::now();

    double tiempo_busqueda = chrono::duration_cast<chrono::nanoseconds>(
        end - start
    ).count() * 1e-9;
    
    cout << "./SuffixArrayPrefixDoubling" << ";" <<
    patrones.size() << ";" << cant_documentos << ";" << tiempo_busqueda << endl;

    return 0;
}
