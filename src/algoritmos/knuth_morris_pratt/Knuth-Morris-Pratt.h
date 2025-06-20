#ifndef KNUTH_MORRIS_PRATT_H
#define KNUTH_MORRIS_PRATT_H

#include <string>
#include <vector>

// Función que computa el arreglo LPS 
void computeLPSArray(std::string pattern, int m, std::vector<int>& LPS);

// Algoritmo KMP para buscar el patrón en el texto
// Retorna un vector con las posiciones iniciales donde se encuentra el patrón
std::vector<int> KMP(std::string pattern, std::string text);

#endif 
