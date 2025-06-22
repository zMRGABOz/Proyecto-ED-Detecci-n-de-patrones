/**
 * Autor principal: Pablo Villagrán Hermanns (pvilla14)
 * Fecha: 20/06/2025
 * Descripción: Implementacion de sufffix array tradicional 
 * Última modificación: 22/06/2025
 * Basandose en: https://www.geeksforgeeks.org/cpp/cpp-program-to-implement-suffix-array/
 * Se implemento personalmente la busqueda binaria doble y la concatenacion de textos 
*/

#include "SuffixArray.h"


vector<int> build_suffix_array(string &texto) {
    int n = texto.length();
    vector<int> sufArr(n);
    vector<string> suf(n);

    //Genera los sufijos, partiendo el texto original
    for (int i = 0; i < n; i++){
        suf[i] = texto.substr(i);
    }
    //La funcion substr toma bastante tiempo,
    //y esto genera que la creacion se demore bastante 

    //Sort que los ordena lexicograficamente, 
    //pero a diferencia del otro algoritmo que usa preffix doubling
    //este compara los sufijos completos, por lo que añade mas tiempo 
    sort(suf.begin(), suf.end());

    //Crea el suffix array a partir de 
    //el tamaño de texto menos el largo del sufijo que
    //se encuentra en la posicion "i"
    for (int i = 0; i < n; i++){
        sufArr[i] = n - suf[i].length();
    }

    return sufArr;  
}


string concatenar_textos(const vector<string>& textos, vector<int>& texto_por_pos) {
    string resultado;
    //guarda a que texto pertenece cada caracter, y lo escribe en el resultado
    for (int i = 0; i < textos.size(); ++i) {
        for (char c : textos[i]) {
            resultado += c;
            texto_por_pos.push_back(i);  // ID del texto
        }
        resultado += '$';                // separador
        texto_por_pos.push_back(-1);     // separador no pertenece a ningún texto
    }

    return resultado;
}

map<int, int> contar_ocurrencias_por_texto(
    const string& texto_total,
    const vector<int>& suffix_array,
    const string& subfrase,
    const vector<int>& texto_por_pos) {

    int n = suffix_array.size();
    int len = subfrase.length();

    int izq = 0, der = n;

    // Buscar lower_bound
    while (izq < der) {
        int mid = (izq + der) / 2;
        string sufijo = texto_total.substr(suffix_array[mid], len);
        if (sufijo < subfrase)
            izq = mid + 1;
        else
            der = mid;
    }

    int lower = izq;

    // Buscar upper_bound
    izq = 0, der = n;
    while (izq < der) {
        int mid = (izq + der) / 2;
        string sufijo = texto_total.substr(suffix_array[mid], len);
        if (sufijo <= subfrase)
            izq = mid + 1;
        else
            der = mid;
    }

    int upper = izq;

    map<int, int> conteo_por_texto;

    for (int i = lower; i < upper; ++i) {
        int pos_global = suffix_array[i]; //la posicion del suffix array donde se encontro el patron
        int id_texto = texto_por_pos[pos_global]; //el vector texto_por_pos sabe a que texto pertence
                                                  //cada caracter, por lo que busca a que texto pertence 
                                                  //y lo guarda
        if (id_texto != -1) {
            conteo_por_texto[id_texto]++; //si resulta que el texto existe, le añade uno para
                                          //señalar que se econtro el patron en ese texto 
        }
    }

    return conteo_por_texto;
}


int main() {
    vector<string> textos = {
        "la casa azul",
        "otra flor roja",
        "el perro duerme en la casa",
        "una flor roja y otra flor roja"
    };

    vector<int> texto_por_pos;
    string texto_total = concatenar_textos(textos, texto_por_pos);
    vector<int> suffix_array = build_suffix_array(texto_total);

    string subfrase = "flor roja";

    map<int, int> resultados = contar_ocurrencias_por_texto(
    texto_total, suffix_array, subfrase, texto_por_pos
    );

    if (!resultados.empty()) {
        for (const auto& [id_texto, cantidad] : resultados) {
            cout << "Subfrase encontrada " << cantidad << " vez" 
                << (cantidad > 1 ? "es" : "") << " en texto #" << id_texto + 1 << "\n";
        }
    } 
    else {
        cout << "Subfrase no encontrada.\n";
    }


    return 0;
}
