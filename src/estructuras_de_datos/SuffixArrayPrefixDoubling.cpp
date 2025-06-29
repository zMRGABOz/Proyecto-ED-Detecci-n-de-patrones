/**
 * Autor principal: Pablo Villagrán Hermanns (pvilla14)
 * Fecha: 20/06/2025
 * Descripción: Implementacion de sufffix array con preffix doubling  
 * Última modificación: 22/06/2025
 * Basandose en: https://www.geeksforgeeks.org/dsa/suffix-array-set-2-a-nlognlogn-algorithm/
 * Se implemento personalmente la busqueda binaria doble y la concatenacion de textos
*/

#include "SuffixArray.h"

using namespace std;

struct Suffix {
    int index;   //indica en que posicion de los textos concatenados se ubica dicho sufijo
    int rank[2]; //son el ranking de posicion de las mmitades del sufijo
                 //se usa para comparar mas rapido, ya que al momento de hacer el sort 
                 //se comparan los sufijos por parte y no en su totalidad 
};

bool cmp(const Suffix &a, const Suffix &b) {
    if (a.rank[0] == b.rank[0]) { //se revisa si son iguales los inicios de las palabras
        return a.rank[1] < b.rank[1]; //se compara la segunda parte de la palabra
    } 
    else {
        return a.rank[0] < b.rank[0];
    }
}

vector<int> build_suffix_array_preffix_doubling(const string &text) {
    int n = text.length(); //largo de los textos concatenados
    vector<Suffix> suffixes(n); // vector donde se gurdaran los indices de los sufijos en orden lexicografico

    for (int i = 0; i < n; i++) { //recorre los indices del texto
        suffixes[i].index = i; //guarda un indice para cada sufijo
        suffixes[i].rank[0] = text[i] - 'a'; //le asigna un rank inicial correspondiente al tamaño
                                             //de la primera letra del sufijo, y le resta "a" para 
                                             //que los valores esten entre 0 y 25
        suffixes[i].rank[1] = (i + 1 < n) ? (text[i + 1] - 'a') : -1; //le asigna un rank al segundo caracter 
                                                                      // si es que existe, en caso de que no
                                                                      //escribe "-1"
    }

    sort(suffixes.begin(), suffixes.end(), cmp); //ordena los prefijos en funcion de los primeros 2 caracteres

    vector<int> ind(n); //vector que indica en que posicion del arreglo ordenado se encuentra cada sufijo
    for (int k = 4; k < 2 * n; k *= 2) { //bucle que crece en potencia de 2, el cual va a recorrer
                                         //los textos y va a ir ordenando los sufijos en funcion de
                                         //los prefijos, ya que compara los primeros k caracteres 
                                         //de cada sufijo para el rank[0], y luego los siguiente k
                                         //caracteres oara el rank[1], de esta forma los va ordenando 
                                         //de a poco y se detiene cuando ya estan todos ordenados
        int rank = 0;
        int prev_rank = suffixes[0].rank[0]; //guarda el menor rango registrado en la pasada anterior
        suffixes[0].rank[0] = rank; //le da un rank 0 al sufijo
        ind[suffixes[0].index] = 0; //guardamos un 0 en la posicion del sufijo con menor rank

        for (int i = 1; i < n; i++) { //empieza de 1 porque ya procesamos el primer sufijo
            if (suffixes[i].rank[0] == prev_rank && suffixes[i].rank[1] == suffixes[i - 1].rank[1]) {
                suffixes[i].rank[0] = rank; //compara el rank del sufijo i con el anterior,
                                            //en caso de ser iguales les da el mismo rank 0
            } else {
                prev_rank = suffixes[i].rank[0]; //si son distintos se modifica el valor con el que se compara 
                suffixes[i].rank[0] = ++rank;    //con el de este sufijo, y aumenta el rank del sufijo
            }
            ind[suffixes[i].index] = i; //guarda en que posicion del arreglo ordenado esta este sufijo
        }

        for (int i = 0; i < n; i++) { //actualizamo el rank[1] de cada sufijo
            int nextindex = suffixes[i].index + k / 2; //tomamos el indice del sufijo mas k/2
            suffixes[i].rank[1] = (nextindex < n) ?  suffixes[ind[nextindex]].rank[0] : -1;
            //operador ternario que indica el valor del rank[1], 
            //el cual dependere de su posicion en el vector ind y de el rank del sufijo en esa posicion
        }

        sort(suffixes.begin(), suffixes.end(), cmp); 
        //ordena los valares lexicograficamente usando la funcion cmp
    }

    vector<int> suffixArr(n);
    for (int i = 0; i < n; i++){
        suffixArr[i] = suffixes[i].index;//crea el suffix array final basandose 
                                         //en los indes del arreglo de sifujos
    }
    
    //retorna el suffixarray final
    return suffixArr;
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
    vector<int> suffix_array = build_suffix_array_preffix_doubling(texto_total);

    string subfrase = "e";

    map<int, int> resultados = contar_ocurrencias_por_texto(
    texto_total, suffix_array, subfrase, largos_textos
    );

    if (!resultados.empty()) {
        for (const auto& [id_texto, cantidad] : resultados) {
            cout << "Subfrase encontrada " << cantidad << " vez" 
                << (cantidad > 1 ? "es" : "") << " en texto #" << id_texto + 1 <<"\n";
        }
    } 
    else {
        cout << "Subfrase no encontrada.\n";
    }

    return 0;
}
