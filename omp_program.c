#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

// --==-- Functions --==========================================================-- //

const int MAX_POWER = 1000;

// Polynomial with MAX_POWER terms (MAX_POWER - i) * x^i
double polynomial(double x) {
    int i;
    double res = 0.0, power = 1.0;
    for (i = 0; i < MAX_POWER; i++) {
        res += (MAX_POWER - i) * power;
        power *= x;
    }
    return power;
}

// --==-- Integral --===========================================================-- //

// Return a random number between 0 and 1
double random_value() {
    return (double) rand() / RAND_MAX;
}

// All integrals are evaluated from 0 to 1
double omp_integral(double (*f)(double), int n_points, int n_threads) {
    int i;
    double res = 0.0;

    #pragma omp parallel private(i) shared(res) num_threads(n_threads)
    {
        #pragma omp for reduction(+:res)
        for (i = 0; i < n_points; i++) {
            res += f(random_value());
        }
    }

    return res / n_points;
}

// --==-- Execution --==========================================================-- //

double omp_timer(double (*f)(double), int n_points, int n_threads, double *res) {
    double start, end, tmp_res;

    start = omp_get_wtime();
    tmp_res = omp_integral(f, n_points, n_threads);
    end = omp_get_wtime();

    if (res) {
        *res = tmp_res;
    }

    return end - start;
}

// Usage: ./a.out n_points n_threads
int main(int argc, char *argv[]) {
    int n_points, n_threads;

    if (argc != 3) {
        printf("Wrong command line arguments\n");
        return 1;
    }

    n_points = atoi(argv[1]);
    n_threads = atoi(argv[2]);

    omp_set_dynamic(0);
    srand(time(NULL));

    printf("Points:  %d\n", n_points);
    printf("Threads: %d\n", n_threads);
    printf("Time:    %lf\n", omp_timer(polynomial, n_points, n_threads, NULL));
    printf("========================\n");

    return 0;
}

