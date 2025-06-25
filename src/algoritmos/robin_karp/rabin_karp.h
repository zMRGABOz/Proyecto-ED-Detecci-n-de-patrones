#ifndef RABIN_KARP_H
#define RABIN_KARP_H

#include <string>
#include <vector>

//Función principal que implementa el algoritmo rabin karp y devuelve el numero de ocurrencias del patrón en el texto
int search_rk(const std::string &pat, const std::string &txt);

#endif 