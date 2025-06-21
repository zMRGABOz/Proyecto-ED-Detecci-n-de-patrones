# Imprimir una cabecera para el archivo CSV
echo "ejecutable;numPatrones;numDocs;tiempo"


for i in 10 20 30 40
do
    for ((c=1; c <= 20; c++))
    do
        for n in 100 200 300 1000 2000
        do
            ../src/algoritmos/knuth_morris_pratt/kmp ../datos_de_pruebas/patrones/patron_${n} ${i}
        done
    done
done