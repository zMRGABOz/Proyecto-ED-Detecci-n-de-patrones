# Para 10 archivos 

for i in 10 40
do
    for ((c=1; c <= 1; c++))
    do
        for n in 100 200
        do
            ../src/algoritmos/boyer_moore/boyer_moore_${i} ../datos_de_pruebas/patrones/patron_${n}
        done
    done
done