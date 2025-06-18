#include <dirent.h>
#include <iostream>
#include "listar_archivos.h"
using namespace std;

void listarArchivos() {
    string dir; 
    string elem;

    DIR *direccion; 
    struct dirent *elementos;
    cout << "Ingrese una ruta: ";
    getline(cin, dir);

    if (direccion=opendir(dir.c_str())){
        while (elementos=readdir(direccion)){
            cout << elementos->d_name << endl;
        }
    }

    closedir(direccion);
}