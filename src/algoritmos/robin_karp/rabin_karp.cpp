 /*
 * Autor principal: Gabriel Catillo Castillo (zMRGABOz)
 * Fecha: 25/06/2025
 * Descripción: Algoritmo Robin-Karp
 * Última modificación: 25/06/2025  
 */

//Fuente: https://www.geeksforgeeks.org/dsa/rabin-karp-algorithm-for-pattern-searching/


#include "rabin_karp.h"
#include <bits/stdc++.h>
using namespace std;

int search_rk(const string &pat, const string &txt){
    
    // Numero de caracteres de entrada (ASCII)
    int d = 256;
    // Número primo para evitar colisiones en el hashing
    int q = 101;
    // Largo del patrón
    int M = pat.length();
    // Largo del texto
    int N = txt.length();
    // Valor hash para el patrón inicializado en 0
    int p = 0;
    // Valor hash para la ventana de texto actual
    int t = 0;
    // Valor que permite eliminar el dígido más significativo al actualizar el hash debido al deslizamiento de la ventana de texto
    int h = 1;
    
    vector<int> ans;
    
    // Se precomputa h = pow(d, M-1) % q
    for (int i = 0; i < M - 1; i++)
        h = (h * d) % q;

    // Se computan los valores hash iniciales para el patrón y para la ventana de texto
    for (int i = 0; i < M; i++){
        
        p = (d * p + pat[i]) % q;
        t = (d * t + txt[i]) % q;
    }

    // Bucle principal encargado de deslizar el patrón sobre el texto
    for (int i = 0; i <= N - M; i++){
        
        // Si los hash del patrón y la ventana de texto coinciden, se procede a comparar si son iguales
        if (p == t){
            bool match = true;
            for (int j = 0; j < M; j++){
                
                if (txt[i + j] != pat[j]){
                
                    match = false;
                    break;
                }
            }
            if (match)
                ans.push_back(i + 1);
        }

        // Se calcula el valor hash para la próxima ventana de texto
        if (i < N - M){
            
            t = (d * (t - txt[i] * h) + txt[i + M]) % q;

            // Se verifica que el valor hash no sea negativo
            if (t < 0)
                t += q;
        }
    }
    return ans.size();
}
