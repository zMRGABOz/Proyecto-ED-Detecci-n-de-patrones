/**
 * Autor principal: Marcos Martínez Rojas (marCRACK29)
 * Fecha: 17/06/2025
 * Descripción: algoritmo Boyer-Moore con la heuristica de Bad Character
 * Última modificación: 17/06/2025
 * Obtenido de: https://www.geeksforgeeks.org/dsa/boyer-moore-algorithm-for-pattern-searching/ 
*/

#include "boyer_moore.h"
#include <iostream>

void badCharHeuristic(string str, int size, int badchar[NO_OF_CHARS]) {
    int i; 

    // llenar badchar con -1 que es el valor por defecto para indicar que 
    // el carácter no existe en el patrón. 
    for (i = 0; i < NO_OF_CHARS; i++)
        badchar[i] = -1; 
    
    // Actualiza con las posiciones reales.
    // La conversion (int)str[i] obtiene el valor ASCII del carácter. 
    for (i = 0; i < size; i++)
        badchar[(int)str[i]] = i;
}

void search(string txt, string pat) {
    int m = pat.size();
    int n = txt.size();

    int badchar[NO_OF_CHARS];

    badCharHeuristic(pat, m, badchar);

    // Desplazamiento del patrón sobre el texto, la iniciamos en cero.
    int s = 0; 

    // Busqueda principal.
    // Recorremos el texto mientras el patrón aún quepa dentro de lo que queda del texto (n-m) 
    while (s <= (n - m)) {
        int j = m - 1; // Se comienza desde el final del patron. De derecha a izquierda

        while (j >= 0 && pat[j] == txt[s + j]) //
            j--;
        
        if (j < 0) {
            cout << "Patrón se produce en el turno = " << s << endl;
            
            // Calcular el nuevo desplazamiento.
            s += (s + m < n) ? m - badchar[txt[s + m]] : 1;
        } else {
            // mismatch o desajuste.
            s += max(1, j - badchar[txt[s + j]]);
        }
    }
}