#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
using namespace std;


/**
 * @brief estructura que contiene informacion de cada sufijo, que corresponden a la ubicacion en el texto
 * y la posiciones en orden de las mitades del sufijo en comparacion a los otros sufijos
 * Esta estructura sirve para hacer mas veloces las comparaciones, 
 * reduciendo el largo de las palabras que se deben comparar a la mitad del largo del sufijo
 */
struct Suffix;

/**
 * @brief compara los ranking de los sufijos,
 * comparando la primera mitad de los sufijos a y b,
 * y luego la segunda mitad, e indica si a debe ir antes que b 
 * en orden lexicografico
 * Esta funcion es entregada como parametro a la 
 * funcion sort de la libreria estandar, 
 * para que la implemente al momento de ordenar los sufijos
 * 
 * @param a el primer sufijo
 * @param b el segundo sufijo para comparar
 * @return true si el rank de a es menor, o false si es mayor, ya sea para el rank 0 o el rank 1
 */
bool cmp(const Suffix &a, const Suffix &b);

/**
 * @brief crea un arreglo de sufijos usando prefix dobling
 * a partir de un texto, y separa los textos a partir del simbolo "$"
 * con una complejidad 
 * O(n * (log n)^2)
 * 
 * @param text el texto a partir del cual se crea el suffix array
 * @return el suffix array con el orden lexicografico de los sufijos
 */
vector<int> build_suffix_array_preffix_doubling(const string &text);

/**
 * @brief crea un arreglo de sufijos de manera simple, 
 * a partir de textos concatenados, con una complejidad 
 * O(n^2 * log n)
 * 
 * @param text el texto a partir del cual se crea el suffix array
 * @return el suffix array con el orden lexicografico de los sufijos
 */
vector<int> build_suffix_array(string &texto);

/**
 * @brief concatena distintos textos obtenidos de varios documentos, 
 * dejando un simbolo "$" entre cada uno de ellos
 * 
 * @param textos vector con los textos que se deben concatenar
 * @return los textos concatenados
 */
string concatenar_textos(const vector<string>& textos);

/**
 * @brief funcion que implementa una doble busqueda binaria, 
 * para encontrar el upper bound, y el lowe bound de las
 * posiciones dentro del suffix array donde se encuentran coincidencias con 
 * el patron de interes
 *  
 * @param texto_total es la concatenacion de todos los textos seprardos po un simbolo "$"
 * @param suffix_array vector con los indices de los sufijos ordenados
 * lexicograficamente
 * @param subfrase es la patron que se intenta localizar en los textos
 * @param largos_textos vector que indica el largo de los textos, mas el signo '$'
 * para separarlos, pero acomodados como suma de prefijos
 * @return un mapa que indica cuantas veces aparece el patron en cada texto
 */
map<int, int> contar_ocurrencias_por_texto(
    const string& texto_total,
    const vector<int>& suffix_array,
    const string& subfrase,
    const vector<int>& largos_textos);