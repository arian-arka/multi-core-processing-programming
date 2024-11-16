void jacobi(float **original, float **copy, int startI, int endI, int lenRow, int lenCol) {
    int i, j;
    int endJ = lenCol - 1;
    for (i = (!startI ? 1 : startI); i <= (endI + 1 == lenRow ? endI - 1 : endI); i++) {
        for (j = 1; j < endJ; j++) {
            copy[i][j] = (original[i][j - 1] + original[i][j + 1] + original[i + 1][j] + original[i - 1][j]) / 4.0;
        }
    }
    for (i = startI; i <= endI; i++) {
        for (j = 1; j < endJ; j++) {
            original[i][j] = copy[i][j];
        }
    }
}