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


string concatenar_textos(const vector<string>& textos) {
    string resultado;
    //guarda a que texto pertenece cada caracter, y lo escribe en el resultado
    for(string s : textos){
        resultado += s;
        resultado += "$";
    }
    return resultado;
}

map<int, int> contar_ocurrencias_por_texto(
    const string& texto_total,
    const vector<int>& suffix_array,
    const string& subfrase,
    const vector<int>& largos_texto) {

    int n = suffix_array.size();
    int len = subfrase.length();

    int izq = 0, der = n;

    // Buscar lower_bound con una busqueda binaria
    while (izq < der) {
        int mid = (izq + der) / 2;
        string sufijo = texto_total.substr(suffix_array[mid], len);
        if (sufijo < subfrase)
            izq = mid + 1;
        else
            der = mid;
    }

    int lower = izq;

    // Buscar upper_bound con una busqueda binaria 
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
        int id_texto;
        for(int t = 0; t < largos_texto.size(); t++){  //por cada pocicion de largo textos tenemos 
            if(pos_global < largos_texto[t]){     //el texto + el caracte '$', por lo que si es igual
                id_texto = t;       //se estaría considerando el caracter '$', lo  cual está mal
                break;              //para ello vemos si es menor, y si lo es, 
            }                       //pertenece a ese texto
            else if(pos_global == largos_texto[t]){
                id_texto = -1;
            }
        }

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
        "una flor roja y otra flor rojae"
    };
    vector<int> largos_textos;
    int acumulado = 0;
    for (const string& s : textos) {
        acumulado += s.length() + 1;  // +1 por el '$'
        largos_textos.push_back(acumulado);
    }
    string texto_total = concatenar_textos(textos);
    vector<int> suffix_array = build_suffix_array(texto_total);

    string subfrase = "e";

    map<int, int> resultados = contar_ocurrencias_por_texto(
    texto_total, suffix_array, subfrase, largos_textos
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
