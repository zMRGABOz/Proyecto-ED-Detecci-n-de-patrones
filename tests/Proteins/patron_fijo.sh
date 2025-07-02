# cantidad de patrones fija en 200 | se recorre una cantidad variable de archivos. 

echo "ejecutable;numPatrones;numDocs;tiempo"

for ((c=1;c<=20;c++))
do
    for n in 5 10 15 20 25 30 35 40
    do  
        ../../src/algoritmos/robin_karp/rk ../datos_de_pruebas/patrones/patrones_protein/patron_200 ../../datos_de_pruebas/documentos/Proteins ${n}
    done
    
    for n in 5 10 15 20 25 30 35 40
    do  
        ../../src/algoritmos/boyer_moore/boyer_moore ../../datos_de_pruebas/patrones/patrones_protein/patron_200 ../../datos_de_pruebas/documentos/Proteins ${n}
    done
    
    for n in 5 10 15 20 25 30 35 40
    do  
        ../../src/algoritmos/knuth_morris_pratt/kmp ../../datos_de_pruebas/patrones/patrones_protein/patron_200 ../../datos_de_pruebas/documentos/Proteins ${n}
    done
done