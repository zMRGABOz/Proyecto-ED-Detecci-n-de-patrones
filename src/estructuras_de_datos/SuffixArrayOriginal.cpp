/**
 * Autor principal: Pablo Villagrán Hermanns (pvilla14)
 * Fecha: 20/06/2025
 * Descripción: Implementacion de sufffix array tradicional 
 * Última modificación: 22/06/2025
 * Basandose en: https://www.geeksforgeeks.org/cpp/cpp-program-to-implement-suffix-array/
 * Se implemento personalmente la busqueda binaria doble y la concatenacion de textos 
*/

#include "SuffixArray.h"


vector<int> build_suffix_array(string &texto) {
    int n = texto.length();
    vector<int> sufArr(n);
    vector<string> suf(n);

    //Genera los sufijos, partiendo el texto original
    for (int i = 0; i < n; i++){
        suf[i] = texto.substr(i);
    }
    //La funcion substr toma bastante tiempo,
    //y esto genera que la creacion se demore bastante 

    //Sort que los ordena lexicograficamente, 
    //pero a diferencia del otro algoritmo que usa preffix doubling
    //este compara los sufijos completos, por lo que añade mas tiempo 
    sort(suf.begin(), suf.end());

    //Crea el suffix array a partir de 
    //el tamaño de texto menos el largo del sufijo que
    //se encuentra en la posicion "i"
    for (int i = 0; i < n; i++){
        sufArr[i] = n - suf[i].length();
    }

    return sufArr;  
}


string concatenar_textos(vector<document>& documentos) {
    string resultado;
    int posicion_actual = 0;

    for (auto& doc : documentos) {
        doc.start_index = posicion_actual;
        resultado += doc.text;
        posicion_actual += doc.text.size();

        resultado += "$"; // delimitador
        posicion_actual += 1;

        doc.end_index = posicion_actual; // posición justo después del $
    }

    return resultado;
}

map<int, int> contar_ocurrencias_por_texto(
    const string& texto_total,
    const vector<int>& suffix_array,
    const string& subfrase,
    const vector<int>& largos_texto) {

    int n = suffix_array.size();
    int len = subfrase.length();

    int izq = 0, der = n;

    // Buscar lower_bound con una busqueda binaria
    while (izq < der) {
        int mid = (izq + der) / 2;
        string sufijo = texto_total.substr(suffix_array[mid], len);
        if (sufijo < subfrase)
            izq = mid + 1;
        else
            der = mid;
    }

    int lower = izq;

    // Buscar upper_bound con una busqueda binaria 
    izq = 0, der = n;
    while (izq < der) {
        int mid = (izq + der) / 2;
        string sufijo = texto_total.substr(suffix_array[mid], len);
        if (sufijo <= subfrase)
            izq = mid + 1;
        else
            der = mid;
    }

    int upper = izq;

    map<int, int> conteo_por_texto;

    for (int i = lower; i < upper; ++i) {
        int pos_global = suffix_array[i]; //la posicion del suffix array donde se encontro el patron
        int id_texto;
        for(int t = 0; t < largos_texto.size(); t++){  //por cada pocicion de largo textos tenemos 
            if(pos_global < largos_texto[t]){     //el texto + el caracte '$', por lo que si es igual
                id_texto = t;       //se estaría considerando el caracter '$', lo  cual está mal
                break;              //para ello vemos si es menor, y si lo es, 
            }                       //pertenece a ese texto
            else if(pos_global == largos_texto[t]){
                id_texto = -1;
            }
        }

        if (id_texto != -1) {
            conteo_por_texto[id_texto]++; //si resulta que el texto existe, le añade uno para
                                          //señalar que se econtro el patron en ese texto 
        }
    }

    return conteo_por_texto;
}



int main(){
    
    string ruta_documentos = "../../datos_de_pruebas/documentos/DNA";

    for (int i = 5; i <= 5; i += 5) {
        vector<document> docs = cargarDocumentos(ruta_documentos, i);
        string texto_total = concatenar_textos(docs); // se concatenan los documentos

        auto crear_sa_start = chrono::high_resolution_clock::now();
        vector<int> suffix_array = build_suffix_array(texto_total);
        auto crear_sa_end = chrono::high_resolution_clock::now();

        double crear_sa_time = chrono::duration_cast<chrono::nanoseconds>(crear_sa_end - crear_sa_start).count();
        cout << "Tiempo creacion SA con " << i << " documentos: " << crear_sa_time << " segundos" << endl;

        // Nombre del archivo binario: DNA_5.bin, DNA_10.bin, etc.
        string tipo_documento = "DNA"; // Puedes ajustarlo dinámicamente si lo necesitas
        string nombre_archivo = "SA_Precompilados/" + tipo_documento + "_" + to_string(i) + ".bin";

        // Abrir archivo en modo binario
        ofstream archivo_bin(nombre_archivo, ios::binary);
        if (!archivo_bin) {
            cerr << "Error al abrir el archivo " << nombre_archivo << " para escritura.\n";
            continue;
        }

        int size = suffix_array.size();

        // Guardar: tamaño, tiempo y datos del suffix array
        archivo_bin.write(reinterpret_cast<char*>(&size), sizeof(int));          // Cantidad de sufijos
        archivo_bin.write(reinterpret_cast<char*>(&crear_sa_time), sizeof(double)); // Tiempo en segundos
        archivo_bin.write(reinterpret_cast<char*>(suffix_array.data()), size * sizeof(int)); // Datos del SA

        archivo_bin.close();
    }

    ruta_documentos = "../../datos_de_pruebas/documentos/English";

    for (int i = 1; i <= 40; i += 5) {
        vector<document> docs = cargarDocumentos(ruta_documentos, i);
        string texto_total = concatenar_textos(docs); // se concatenan los documentos

        auto crear_sa_start = chrono::high_resolution_clock::now();
        vector<int> suffix_array = build_suffix_array(texto_total);
        auto crear_sa_end = chrono::high_resolution_clock::now();

        double crear_sa_time = chrono::duration_cast<chrono::nanoseconds>(crear_sa_end - crear_sa_start).count();
        cout << "Tiempo creacion SA con " << i << " documentos: " << crear_sa_time << " segundos" << endl;

        // Nombre del archivo binario: DNA_5.bin, DNA_10.bin, etc.
        string tipo_documento = "English"; // Puedes ajustarlo dinámicamente si lo necesitas
        string nombre_archivo = "SA_Precompilados/" + tipo_documento + "_" + to_string(i) + ".bin";

        // Abrir archivo en modo binario
        ofstream archivo_bin(nombre_archivo, ios::binary);
        if (!archivo_bin) {
            cerr << "Error al abrir el archivo " << nombre_archivo << " para escritura.\n";
            continue;
        }

        int size = suffix_array.size();

        // Guardar: tamaño, tiempo y datos del suffix array
        archivo_bin.write(reinterpret_cast<char*>(&size), sizeof(int));          // Cantidad de sufijos
        archivo_bin.write(reinterpret_cast<char*>(&crear_sa_time), sizeof(double)); // Tiempo en segundos
        archivo_bin.write(reinterpret_cast<char*>(suffix_array.data()), size * sizeof(int)); // Datos del SA

        archivo_bin.close();
    }


    ruta_documentos = "../../datos_de_pruebas/documentos/Proteins";
    
    for (int i = 5; i <= 40; i += 5) {
        vector<document> docs = cargarDocumentos(ruta_documentos, i);
        string texto_total = concatenar_textos(docs); // se concatenan los documentos

        auto crear_sa_start = chrono::high_resolution_clock::now();
        vector<int> suffix_array = build_suffix_array(texto_total);
        auto crear_sa_end = chrono::high_resolution_clock::now();

        double crear_sa_time = chrono::duration_cast<chrono::nanoseconds>(crear_sa_end - crear_sa_start).count();
        cout << "Tiempo creacion SA con " << i << " documentos: " << crear_sa_time << " segundos" << endl;

        // Nombre del archivo binario: DNA_5.bin, DNA_10.bin, etc.
        string tipo_documento = "Proteins"; // Puedes ajustarlo dinámicamente si lo necesitas
        string nombre_archivo = "SA_Precompilados/" + tipo_documento + "_" + to_string(i) + ".bin";

        // Abrir archivo en modo binario
        ofstream archivo_bin(nombre_archivo, ios::binary);
        if (!archivo_bin) {
            cerr << "Error al abrir el archivo " << nombre_archivo << " para escritura.\n";
            continue;
        }

        int size = suffix_array.size();

        // Guardar: tamaño, tiempo y datos del suffix array
        archivo_bin.write(reinterpret_cast<char*>(&size), sizeof(int));          // Cantidad de sufijos
        archivo_bin.write(reinterpret_cast<char*>(&crear_sa_time), sizeof(double)); // Tiempo en segundos
        archivo_bin.write(reinterpret_cast<char*>(suffix_array.data()), size * sizeof(int)); // Datos del SA

        archivo_bin.close();
    }

    ruta_documentos = "../../datos_de_pruebas/documentos/Sources";

    for (int i = 5; i <= 40; i += 5) {
        vector<document> docs = cargarDocumentos(ruta_documentos, i);
        string texto_total = concatenar_textos(docs); // se concatenan los documentos

        auto crear_sa_start = chrono::high_resolution_clock::now();
        vector<int> suffix_array = build_suffix_array(texto_total);
        auto crear_sa_end = chrono::high_resolution_clock::now();

        double crear_sa_time = chrono::duration_cast<chrono::nanoseconds>(crear_sa_end - crear_sa_start).count();
        cout << "Tiempo creacion SA con " << i << " documentos: " << crear_sa_time << " segundos" << endl;

        // Nombre del archivo binario: DNA_5.bin, DNA_10.bin, etc.
        string tipo_documento = "Sources"; // Puedes ajustarlo dinámicamente si lo necesitas
        string nombre_archivo = "SA_Precompilados/" + tipo_documento + "_" + to_string(i) + ".bin";

        // Abrir archivo en modo binario
        ofstream archivo_bin(nombre_archivo, ios::binary);
        if (!archivo_bin) {
            cerr << "Error al abrir el archivo " << nombre_archivo << " para escritura.\n";
            continue;
        }

        int size = suffix_array.size();

        // Guardar: tamaño, tiempo y datos del suffix array
        archivo_bin.write(reinterpret_cast<char*>(&size), sizeof(int));          // Cantidad de sufijos
        archivo_bin.write(reinterpret_cast<char*>(&crear_sa_time), sizeof(double)); // Tiempo en segundos
        archivo_bin.write(reinterpret_cast<char*>(suffix_array.data()), size * sizeof(int)); // Datos del SA

        archivo_bin.close();
    }

}


//g++ .\SuffixArrayOriginal.cpp  ../leer_archivos.cpp -o SuffixArrayOriginal
//./SuffixArrayOriginal


//codigo para generar suffix array  precomputados
/*
int main(int argc,  char** argv) {
    
    if(argc < 3){ 
       cerr << "Uso: " << argv[0] << " <ruta a patron> <numero de archivos>" << endl;
       return 1;
    }
    string ruta_documentos = "../../datos_de_pruebas/documentos/DNA";
    string ruta_patron = argv[1];
    int cant_documentos = atoi(argv[2]);
    vector<document> docs = cargarDocumentos(ruta_documentos, cant_documentos);
    vector<string> patrones = cargarPatrones(ruta_patron);


    vector<int> largos_textos;
    int acumulado = 0;

    for (const auto& d : docs) {
        acumulado += d.text.length() + 1;  // +1 por el '$'
        largos_textos.push_back(acumulado);
    }

    string texto_total = concatenar_textos(docs);
    auto crear_sa_start = chrono::high_resolution_clock::now();
    vector<int> suffix_array = build_suffix_array(texto_total);
    auto crear_sa_end = chrono::high_resolution_clock::now();

    double crear_sa_time = chrono::duration_cast<chrono::nanoseconds>(crear_sa_end - crear_sa_start).count();
    cout << crear_sa_time * 1e-9 << endl;
    cout << "lol" << endl;
    map<int,int> resultados;
    for(string s : patrones){
        string patron = s;
        
        auto encontrar_sa_start = chrono::high_resolution_clock::now();
        resultados = contar_ocurrencias_por_texto(
        texto_total, suffix_array, patron, largos_textos
        );
        auto encontrar_sa_end = chrono::high_resolution_clock::now();

        double encontrar_sa_time = chrono::duration_cast<chrono::nanoseconds>(encontrar_sa_end - encontrar_sa_start).count();
        
        cout << encontrar_sa_time * 1e-9 << endl;

        if (!resultados.empty()) {
            for (const auto& [id_texto, cantidad] : resultados) {
                cout << "Patron: " << patron <<" encontrado " << cantidad << " vez" 
                    << (cantidad > 1 ? "es" : "") << " en texto #" << id_texto + 1 <<"\n";
            }
        } 

        else {
            cout << "Patron no encontrada.\n";
        }
    }

    return 0;
}
*/