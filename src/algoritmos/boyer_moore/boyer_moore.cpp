/**
 * Autor principal: Marcos Martínez Rojas (marCRACK29)
 * Fecha: 17/06/2025
 * Descripción: algoritmo Boyer-Moore 
 * Última modificación: 01/07/2025
 * Basandose en: https://www.geeksforgeeks.org/dsa/boyer-moore-algorithm-for-pattern-searching/ 
*/

#include "boyer_moore.h"
#include <iostream>

void badCharHeuristic(string pat, int size, int badchar[NO_OF_CHARS]) {
    // llenar badchar con -1 que es el valor por defecto para indicar que 
    // el carácter no existe en el patrón. 
    for (int i = 0; i < NO_OF_CHARS; i++)
        badchar[i] = -1; 
    
    // Actualiza con las posiciones reales.
    // La conversion (int)str[i] obtiene el valor ASCII del carácter. 
    for (int i = 0; i < size; i++)
        badchar[(unsigned char)pat[i]] = i;
}

int searchBM(const string& txt, const string& pat) {
    int count = 0;
    int m = pat.size();
    int n = txt.size();

    if (m == 0 || n == 0 || m > n) return 0;

    int badchar[NO_OF_CHARS];
    badCharHeuristic(pat, m, badchar);

    // Desplazamiento del patrón sobre el texto, la iniciamos en cero.
    int s = 0; 

    // Busqueda principal.
    // Recorremos el texto mientras el patrón aún quepa dentro de lo que queda del texto (n-m) 
    while (s <= (n - m)) {
        int j = m - 1; // Se comienza desde el final del patron. De derecha a izquierda

        while (j >= 0 && pat[j] == txt[s + j])
            j--;
        
        if (j < 0) {
            //cout << "Patrón se produce en el turno = " << s << endl;
            count ++;
            // Calcular siguiente desplazamiento
            // Si hay más texto después del patrón, usar bad character
            // Si no, mover al menos 1 posición
            s += (s + m < n) ? m - badchar[(unsigned char)txt[s + m]] : 1;
        } else {
            // mismatch
            int bad_char_shift = j - badchar[(unsigned char)txt[s + j]];
            // Tomar el máximo desplazamiento, pero al menos 1
             s += max(1, bad_char_shift);
        }
    }

    return count;
}