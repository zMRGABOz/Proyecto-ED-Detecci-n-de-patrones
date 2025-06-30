echo "ejecutable;numPatrones;freq;tiempo"

for ((c=1;c<=20;c++))
do
    for n in 100 200 300 400
    do 
        ../src/estructuras_de_datos/SuffixArrayPrefixDoubling.exe ../datos_de_pruebas/patrones/patron_${n}
    done

    # Resto de las implementaciones
done