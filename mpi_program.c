#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

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

// Return a random number between 0 and 1
double random_value() {
    return (double) rand() / RAND_MAX;
}


int main(int argc, char *argv[]) {
    int i, n_points, n_threads, rank;
    double local_res = 0.0, res, start, end;

    if (argc != 2) {
        printf("Wrong command line arguments\n");
        return 1;
    }

    n_points = atoi(argv[1]);

    srand(time(NULL));

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &n_threads);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    start = MPI_Wtime();

    if (rank != 0) {
        for (i = rank - 1; i < n_points; i += n_threads - 1) {
            local_res += polynomial(random_value());
        }
    }

    MPI_Reduce(&local_res, &res, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    res = res / n_points;

    end = MPI_Wtime();

    if (rank == 0) {
        printf("Points:  %d\n", n_points);
        printf("Threads: %d\n", n_threads);
        printf("Time:    %lf\n", end - start);
        printf("Result:  %lf\n", res);
    }

    MPI_Finalize();
    return 0;
}
