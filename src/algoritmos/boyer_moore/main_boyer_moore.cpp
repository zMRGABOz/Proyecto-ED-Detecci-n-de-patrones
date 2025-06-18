#include "boyer_moore.h"
#include "../../listar_archivos.h"

// compilar con: 
// g++ -o boyer_moore main_boyer_moore.cpp boyer_moore.cpp ../../listar_archivos.cpp -I../../
// ./boyer_moore

int main() {
    string txt = "ABAAABCDABAA";
    string pat = "ABAA";
    search(txt, pat);

    listarArchivos();

    return 0;
}