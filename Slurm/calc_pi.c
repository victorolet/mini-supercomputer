#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>
#include <time.h>

#define TOTAL_POINTS 1000000000

int main(int argc, char** argv) {
    int rank, size;
    int points_inside_circle = 0;
    double x, y, distance;
    double pi_estimate;
    double start_time, end_time;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Seed the random number generator based on the rank
    srand((unsigned int)(time(NULL) + rank));

    // Each process performs a portion of the iterations
    int iterations_per_process = TOTAL_POINTS / size;

    // Synchronize all processes before starting the timer
    MPI_Barrier(MPI_COMM_WORLD);
    start_time = MPI_Wtime();

    for (int i = 0; i < iterations_per_process; i++) {
        // Generate random coordinates
        x = (double)rand() / RAND_MAX;
        y = (double)rand() / RAND_MAX;

        // Check if the point is inside the quarter circle
        distance = x * x + y * y;
        if (distance <= 1.0) {
            points_inside_circle++;
        }
    }
    
   // Sum up the results from all processes
    int total_points_inside_circle;
    MPI_Reduce(&points_inside_circle, &total_points_inside_circle, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    // Process 0 calculates the final pi estimate
    if (rank == 0) {
        pi_estimate = (double)total_points_inside_circle / TOTAL_POINTS * 4.0;
        printf("Estimated value of pi: %f\n", pi_estimate);
    }

    // Synchronize all processes after computation
    MPI_Barrier(MPI_COMM_WORLD);
    end_time = MPI_Wtime();

    // Process 0 prints the execution time
    if (rank == 0) {
        printf("Execution time: %f seconds\n", end_time - start_time);
    }

    MPI_Finalize();

    return 0;
}

