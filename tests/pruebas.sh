echo "ejecutable;numPatrones;freq;tiempo"

for i in 5 10 15 20 25 30 35 40
do
    for ((c=1; c <= 20; c++))
    do
        for n in 100 200 300 1000 2000
        do
            ../src/algoritmos/boyer_moore/boyer_moore_${i} ../datos_de_pruebas/patrones/patron_${n}
        done

        for n in 100 200 300 1000 2000
        do
            ../src/algoritmos/knuth_morris_pratt/kmp_${i} ../datos_de_pruebas/patrones/patron_${n} 
        done
    done
done