#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#define SIZE 10
void saveMatrixToFile(const char *path, float matrix[SIZE][SIZE], int lenRow, int lenCol) {
    FILE *fp = fopen(path, "w");
    fprintf(fp, "%d %d\n", lenRow,lenCol);
    for (int i = 0; i < lenRow; i++) {
        for (int j = 0; j < lenCol; j++) {
            fprintf(fp, "%.2f\t", matrix[i][j]);
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
}

int main(int argc, char *argv[]) {
    float temperature[SIZE][SIZE];
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if(!i || !j || j==SIZE-1 || i==SIZE-1)
                temperature[i][j]=100;
            else
                temperature[i][j]=0;
        }
    }
    saveMatrixToFile("mat.txt", temperature, SIZE, SIZE);

    return 0;
}