# Cantidad fija de archivos = 40 | cantidad de patrones variables.
# Un aproximado de 800.000 lineas en el csv
echo "ejecutable;numPatrones;freq;tiempo"

for ((c=1;c<=20;c++))
do
    for n in 100 200 300 400
    do 
        ../src/algoritmos/boyer_moore/boyer_moore_40 ../datos_de_pruebas/patrones/patron_${n}
    done

    # Resto de las implementaciones
done