#include <bits/stdc++.h>
using std::string;
using std::vector;
using std::ifstream;
using std::ofstream;
using std::cout;
using std::endl;
using std::filesystem::directory_iterator;

string obtenerFragmentoAleatorio(const string& texto, std::mt19937& gen, int largo_min = 8, int largo_max = 20) {
    if (texto.size() < largo_min) return "";

    std::uniform_int_distribution<> dist_largo(largo_min, largo_max);
    int largo = dist_largo(gen);
    std::uniform_int_distribution<> dist_inicio(0, texto.size() - largo);

    int inicio = dist_inicio(gen);
    return texto.substr(inicio, largo);
}




int main(){
   const string ruta_entrada = "../datos_de_pruebas/documentos/";
   const string ruta_salida = "../datos_de_pruebas/patrones/";
   vector<string> todos; // Vector de documentos, cada elemento es el contenido de un documento

   for(const auto& file: directory_iterator(ruta_entrada)){
        ifstream archivo(file.path());
        string aux;
        while (! archivo.eof()) {
            string linea;
            getline(archivo,linea);
            aux+=linea;
        }
        todos.push_back(aux); // Se añade el contenido de un archivo a un elemento del vector
        archivo.close();
    }

    std::random_device rd;
    std::mt19937 gen(rd());

    for(int i : {100, 200, 300, 400, 500, 1000, 2000}){
        vector<string> patrones;
        std::unordered_set<string> usados; //para evitar patrones usados
        int iterador = 0;
        while (patrones.size() < i) {
            string fragmento = obtenerFragmentoAleatorio(todos[iterador % todos.size()], gen);
            iterador++;
            if (!fragmento.empty() && usados.find(fragmento) == usados.end()) {
                patrones.push_back(fragmento);
                usados.insert(fragmento);
            }
        }
         // Guardar en archivo
        string nombre_archivo = ruta_salida + "patron_" + std::to_string(i);
        ofstream salida(nombre_archivo);
        for (const auto& f : patrones) {
            salida << f << "\n";
        }
        salida.close();

        cout << "Guardado: " << nombre_archivo << " (" << i << " patrones)\n";

    }
}