echo "" > omp_result.txt

for n in {0..5..1}
do
    for t in {0..5..1}
    do
        ./omp $(((2 ** $n) * 100000)) $((2 ** $t)) >> omp_result.txt
    done
done
