/**
 * Autor principal: Marcos Martínez Rojas (marCRACK29)
 * Fecha: 17/06/2025
 * Descripción: algoritmo Boyer-Moore 
 * Última modificación: 17/06/2025
 * Basandose en: https://www.geeksforgeeks.org/dsa/boyer-moore-algorithm-for-pattern-searching/ 
 * Se añade la heuristica de good suffix. 
*/

#include "boyer_moore.h"
#include <iostream>

void badCharHeuristic(string str, int size, int badchar[NO_OF_CHARS]) {
    // llenar badchar con -1 que es el valor por defecto para indicar que 
    // el carácter no existe en el patrón. 
    for (int i = 0; i < NO_OF_CHARS; i++)
        badchar[i] = -1; 
    
    // Actualiza con las posiciones reales.
    // La conversion (int)str[i] obtiene el valor ASCII del carácter. 
    for (int i = 0; i < size; i++)
        badchar[(int)str[i]] = i;
}

void preprocessGoodSuffix(string pat, int m, int shift[], int suffix[]) {
    int i = m, j = m + 1;
    suffix[i] = j;

    while (i > 0) {
        while (j <= m && pat[i - 1] != pat[j - 1]) {
            if (shift[j] == 0)
                shift[j] = j - i;
            j = suffix[j];
        }
        i--; j--;
        suffix[i] = j;
    }

    // Preprocesar shift[]
    j = suffix[0];
    for (int i = 0; i <= m; i++) {
        if (shift[i] == 0)
            shift[i] = j;
        if (i == j)
            j = suffix[j];
    }
}

int searchBM(const string& txt, const string& pat) {
    // vector<int> posiciones;
    int count = 0;
    int m = pat.size();
    int n = txt.size();

    if (m == 0 || n == 0 || m > n) return 0;

    int badchar[NO_OF_CHARS];
    badCharHeuristic(pat, m, badchar);

    int *shift = new int[m + 1]();   // Inicializa en 0
    int *suffix = new int[m + 1];

    preprocessGoodSuffix(pat, m, shift, suffix);

    // Desplazamiento del patrón sobre el texto, la iniciamos en cero.
    int s = 0; 

    // Busqueda principal.
    // Recorremos el texto mientras el patrón aún quepa dentro de lo que queda del texto (n-m) 
    while (s <= (n - m)) {
        int j = m - 1; // Se comienza desde el final del patron. De derecha a izquierda

        while (j >= 0 && pat[j] == txt[s + j])
            j--;
        
        if (j < 0) {
            cout << "Patrón se produce en el turno = " << s << endl;
            // posiciones.push_back(s);
            count ++;
            // Calcular el nuevo desplazamiento.
            //s += (s + m < n) ? m - badchar[txt[s + m]] : 1;
            s += shift[0];
        } else {
            // mismatch o desajuste.
            //s += max(1, j - badchar[txt[s + j]]);

            int bc_shift = max(1, j - badchar[(int)txt[s + j]]);
            int gs_shift = shift[j + 1];
            s += max(bc_shift, gs_shift);
        }
    }
    delete[] shift;
    delete[] suffix;

    return count;
}