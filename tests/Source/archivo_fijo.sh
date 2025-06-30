# Cantidad fija de archivos = 20 | cantidad de patrones variables.
echo "ejecutable;numPatrones;numDocs;tiempo"

for ((c=1;c<=20;c++))
do
    for n in 100 300 500
    do 
        ../../src/algoritmos/boyer_moore/boyer_moore ../../datos_de_pruebas/patrones/patrones_sources/patron_${n} ../../datos_de_pruebas/documentos/Sources 20
    done

    for n in 100 300 500
    do 
        ../../src/algoritmos/knuth_morris_pratt/kmp ../../datos_de_pruebas/patrones/patrones_sources/patron_${n} ../../datos_de_pruebas/documentos/Sources 20
    done

    for n in 100 300 500 
    do 
        ../../src/algoritmos/robin_karp/rk ../../datos_de_pruebas/patrones/patrones_sources/patron_${n} ../../datos_de_pruebas/documentos/Sources 20
    done 
done