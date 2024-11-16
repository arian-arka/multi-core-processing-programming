#include <stdlib.h>

float **readMatrixOfFile(int *lenRow, int *lenCol, const char *path) {
    FILE *pf = fopen(path, "r");
    int i, j;
    fscanf(pf, "%d", lenRow);
    fscanf(pf, "%d", lenCol);
    float **matrix = (float **) malloc((*lenRow) * sizeof(float *));
    for (i = 0; i < *lenRow; i++) {
        matrix[i] = (float *) malloc((*lenCol) * sizeof(float));
        for (j = 0; j < *lenCol; j++)
            fscanf(pf, "%f", &matrix[i][j]);
    }
    fclose(pf);
    return matrix;
}

void saveMatrixToFile(const char *path, float **matrix, int lenRow, int lenCol) {
    FILE *fp = fopen(path, "w");
    int i, j;
    for (i = 1; i < lenRow-1; i++) {
        for (j = 1; j < lenCol-1; j++) {
            fprintf(fp, "%.2f\t", matrix[i][j]);
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
}

