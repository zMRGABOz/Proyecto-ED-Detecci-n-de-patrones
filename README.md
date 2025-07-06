# Proyecto de Búsqueda de Patrones en Documentos

Este proyecto implementa diferentes algoritmos y estructuras de datos para la búsqueda eficiente de patrones en múltiples documentos.

## 📁 Estructura del Proyecto

```
.
├── src/                    # Código fuente
│   ├── algoritmos/        # Implementaciones de algoritmos de búsqueda
│   └── estructuras_de_datos/   # Implementaciones de estructuras de datos
|   |    └── SA_PD_Precompilados/ # Estructura suffix array precompilada (ya construidas) en archivos binarios. 
├── tests/                 # Tests de algoritmos y estructuras de datos implementadas junto con sus resultados
├── datos_de_pruebas/      # Conjunto de datos para pruebas
└── utils/            # Funciones que son utilizadas para el proyecto
```

## Algoritmos Implementados

### Soluciones Algorítmicas
- Boyer-Moore (con badchar heuristic).
- Knuth-Morris-Pratt. 
- Rabin-Karp.

### Soluciones basadas en Estructuras de Datos
- Suffix Array (con Prefix doubling).

## Instrucciones de uso
Una vez clonado el repositorio y teniendo descargados los datasets: DNA, English, Proteins, Sources. Se debe proceder a crear los patrones existentes compilando el archivo utils/creador_patrones.cpp .
```
g++ -o creador creador_patrones.cpp
```
Luego ir modificando la ruta de entrada y de salida.
Una vez teniendo los patrones, se puede ejecutar el archivo utils/insertar_aleatorio.cpp
modificando la ruta de entrada y salida. 
```
g++ -o nopatron insertar_aleatorio.cpp 
```
Además se deben precomputar las estructuras, ejecutando el archivo src/estructuras_de_datos/main_precomputar.cpp .
```
g++ -o precomputar main_precomputar.cpp SuffixArrayPrefixDoubling.cpp ../leer_archivos.cpp
```
Por último, se debe compilar cada uno de los algoritmos (funciones main solamente).
Una vez hecho todo lo anterior, se puede proceder a correr algun tipo de test. Para ello, primero debe posicionarse en la carpeta test y ejecutar, por ejemplo (Dentro de DNA): 
```
bash archivo_fijo.sh > a_resultados_archivo_fijo_dna.csv
```

## 👥 Contribuidores
- Marcos Martínez
- Pablo Villagran
- Gabriel Castillo

