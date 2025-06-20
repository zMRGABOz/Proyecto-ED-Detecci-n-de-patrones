 /*
 * Autor principal: Gabriel Catillo Castillo (zMRGABOz)
 * Fecha: 16/06/2025
 * Descripción: Algoritmo Knuth-Morris-Pratt
 * Última modificación: 16/06/2025  
 */

 //Implementación basada en: https://www.geeksforgeeks.org/cpp/knuth-morris-pratt-in-c/
#include "Knuth-Morris-Pratt.h"
#include <bits/stdc++.h>
using namespace std;

// Función que computa el arreglo LPS
void computeLPSArray(string pattern,  int m, vector<int> &LPS) {
    int length = 0;
    LPS[0] = 0; // LPS[0] siempre es 0
    int i = 1;

    //Ciclo while en donde se construye el arreglo LPS, donde cada posición nos dice
    //cuál es la longitud del prefijo más largo que también es sufijo
    while (i < m) {
        if (pattern[i] == 
            pattern[length]) {
            length++;
            LPS[i] = length;
            i++;
        }
        else {
            if (length != 0) {
                length = LPS[length - 1];
            }
            else {
                LPS[i] = 0;
                i++;
            }
        }
    }
}

// Algoritmo KPM para buscar el patrón en el texto
vector<int> KMP(string pattern, string text) {

    int m = pattern.length(); //Se almacena tamaño del patrón
    int n = text.length(); //Se almacena tamaño del texto

    // Arreglo para almacenar los índices del patrón en el texto
    vector<int> ans;

    vector<int> LPS(m);
    computeLPSArray(pattern, m, LPS);

    int i = 0; // índice para el texto
    int j = 0; // índice para el patrón
    while (i < n) {

        // Si los caracteres coinciden se aumentan los indices
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }

        // Cuando el patrón coincide completamente,
        // Se almacena la posición del patrón en el texto
        if (j == m) {
            ans.push_back(i - j);
            j = LPS[j - 1];
        }
        // Cuando un caracter no coincide,
        // se usa el arreglo LPS para volver retroceder en el patron
        // (esto evita comparaciones innecesarias   )
        else if (i < n && pattern[j]
                 != text[i]) {
            if (j != 0) {
                j = LPS[j - 1];
            }
            else {
                i++;
            }
        }
    }
    return ans;
}