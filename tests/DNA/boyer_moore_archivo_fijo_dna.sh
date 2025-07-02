# Cantidad fija de archivos = 20 | cantidad de patrones variables.
echo "ejecutable;numPatrones;numDocs;tiempo"

for ((c=1;c<=20;c++))
do
    for n in 100 300 500
    do 
        ../../src/algoritmos/boyer_moore/boyer_moore ../../datos_de_pruebas/patrones/patrones_dna/patron_${n} ../../datos_de_pruebas/documentos/DNA 20
    done
done