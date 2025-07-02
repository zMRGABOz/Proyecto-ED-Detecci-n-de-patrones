echo "ejecutable;numPatrones;numDocs;tiempo"
for n in 100 300 500
do 
    ../src/algoritmos/boyer_moore/boyer_moore ../datos_de_pruebas/patrones/patrones_english/patron_${n} ../datos_de_pruebas/documentos/English 20
done