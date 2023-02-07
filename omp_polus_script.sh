for n in {0..5..1}
do
    for t in {0..5..1}
    do
        bsub -n $((2 ** $t)) -W 00:15 -o omp_result_$n_$t.out -e omp_result_$n_$t.err ./omp $(((2 ** $n) * 100000))
    done
done
