# cantidad de patrones fija en 300 | se recorre una cantidad variable de archivos. 
# Aproximado de 990.000 lineas
echo "ejecutable;numPatrones;numDocs;tiempo"

for ((c=1;c<=20;c++))
do
    for n in 5 10 20 25 30 35 40
    do  
        ../src/algoritmos/robin_karp/rk ../datos_de_pruebas/patrones/patron_300 ${n}
    done

    # Resto de las implementaciones
done