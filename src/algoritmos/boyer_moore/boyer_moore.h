#ifndef BOYER_MOORE_H
#define BOYER_MOORE_H
#define NO_OF_CHARS 256 // 256 para ASCII estándar
#include <string>
#include <vector>
using namespace std; 

/**
 * @brief preprocesa el patrón y crea un arreglo que almacena la última posición de cada caracter 
 * en el patrón. 
 * 
 * @param pat el patrón que se quiere buscar.
 * @param size longitud del patrón.
 * @param badchar arreglo de tamaño fijo que almacena la última pos. de cada carácter en el patrón.
 */
void badCharHeuristic(string pat, int size, int badchar[NO_OF_CHARS]);

/**
 * @brief implementa el algoritmo de busqueda de Boyer-Moore utilizando las heuristicas Good Suffix
 * y Bad Character para encontrar todas las ocurrencias de un patrón dentro de un texto. 
 * 
 * @param txt el texto donde se buscará el patrón. 
 * @param pat el patrón que se desea encontrar. 
 * @return cantidad de veces que aparece el patrón en el texto
 */
int searchBM(const string& txt, const string& pat);

#endif