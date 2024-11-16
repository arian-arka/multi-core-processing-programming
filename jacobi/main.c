#include <stdio.h>
#include <mpi.h>
#include "file.h"
#include "calc.h"
#include <string.h>
#include <mpi.h>

float **malloc2dfloat(int lenRow, int lenCol) {
    float **matrix = (float **) malloc(lenRow * sizeof(float *));
    for (int i = 0; i < lenRow; i++)
        matrix[i] = (float *) malloc(lenCol * sizeof(float));
    return matrix;
}

void free2d(float **matrix, int len) {
    for (int i = 0; i < len; i++)
        free(matrix[i]);
    free(matrix);
}

void printAll(float **matrix, int len) {
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len; j++) {
            printf("%.2f\t", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    printf("\n");
}

int main(int argc, char *argv[]) {
    int steps;
    int lenRow, lenCol, size, rank = 0, i, j;
    float **original = readMatrixOfFile(&lenRow, &lenCol, "mat.txt");
    float **copy = malloc2dfloat(lenRow, lenCol);
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    steps = 100;
//    steps = argc > 1 ? atoi(argv[1]) : 100;
    if (!rank)
        printf("steps:%d\n", steps);

    int numberOfRows = lenRow / size;
    int startI = rank * numberOfRows;
    int endI = startI + numberOfRows - 1;

    for (; steps; steps--) {
        if (rank < size - 1) {
            MPI_Send(original[endI], lenCol, MPI_FLOAT, rank + 1, 0, MPI_COMM_WORLD);
            MPI_Recv(original[endI + 1], lenCol, MPI_FLOAT, rank + 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
        if (rank > 0) {
            MPI_Send(original[startI], lenCol, MPI_FLOAT, rank - 1, 0, MPI_COMM_WORLD);
            MPI_Recv(original[startI - 1], lenCol, MPI_FLOAT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }

        jacobi(original, copy, startI, endI, lenRow, lenCol);
    }

    if (!rank)
        for (i = 1; i < size; i++)
            MPI_Recv(original[i * numberOfRows], numberOfRows * lenCol, MPI_FLOAT, i, 0, MPI_COMM_WORLD,
                     MPI_STATUS_IGNORE);
    else
        MPI_Send(original[startI], numberOfRows * lenCol, MPI_FLOAT, 0, 0, MPI_COMM_WORLD);

    if (!rank)
        saveMatrixToFile("newMat.txt", original, lenRow, lenCol);

    MPI_Finalize();
    free2d(original, lenRow);
    free2d(copy, lenRow);

    return 0;
}