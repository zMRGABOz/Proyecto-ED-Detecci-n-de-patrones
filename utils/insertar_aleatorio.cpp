#include <iostream>
#include <fstream>
#include <string>
#include <random>

void insertarElemAleatorios(const std::string& archivo_entrada, const std::string& archivo_salida) {
    std::ifstream entrada(archivo_entrada);
    std::ofstream salida(archivo_salida);

    if (!entrada.is_open()) {
        std::cerr << "No se pudo abrir el archivo de entrada.\n";
        return;
    }

    std::random_device rd;
    std::mt19937 gen(rd());

    std::string linea;
    while (std::getline(entrada, linea)) {
        std::uniform_int_distribution<> dist(0, linea.size()); // puede ser al inicio o al final también
        int pos = dist(gen);

        linea.insert(pos, "ç"); 
        // para ADN, inglés, protein = ñ o Ñ
        // para sources = ç
        salida << linea << "\n";
    }

    entrada.close();
    salida.close();

    std::cout << "Archivo modificado guardado en: " << archivo_salida << "\n";
}

int main() {
    std::string entrada = "../datos_de_pruebas/patrones/patrones_sources/patron_100";
    std::string salida = "../datos_de_pruebas/patrones/no_patron_sources/patron_100";

    insertarElemAleatorios(entrada, salida);

    return 0;
}
