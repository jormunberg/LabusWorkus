#include "matrix.h"

matrix createMatrix(int nRows, int nCols) {
    int **values = (int **) malloc(sizeof(int *) * nRows);
    for (int i = 0; i < nRows; i++)
        values[i] = (int *) malloc(sizeof(int) * nCols);
    return (matrix) {values, nRows, nCols};
}

matrix *getMemArrayOfMatrices(int nMatrices,
                              int nRows, int nCols) {
    matrix *ms = (matrix *) malloc(sizeof(matrix) * nMatrices);
    for (int i = 0; i < nMatrices; i++)
        ms[i] = createMatrix(nRows, nCols);
    return ms;
}

void freeMemMatrix(matrix m) {
    for (int i = 0; i < m.nRows; ++i) {
        free(m.values[i]);
    }
    free(m.values);
}

void freeMemMatrices(matrix *ms, int nMatrices) {
    for (int i = 0; i < nMatrices; ++i) {
        freeMemMatrix(ms[i]);
    }
    free(ms);
}

void inputMatrix(matrix *m) {
    for (int i = 0; i < m->nRows; i++) {
        for (int j = 0; j < m->nCols; j++) {
            scanf("%d", &m->values[i][j]);
        }
    }
}

void inputMatrices(matrix *ms, int nMatrices) {
    for (int i = 0; i < nMatrices; ++i) {
        inputMatrix(&ms[i]);
    }
}

void outputMatrix(matrix m) {
    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            printf("%d ", m.values[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void outputMatrices(matrix *ms, int nMatrices) {
    for (int i = 0; i < nMatrices; ++i) {
        outputMatrix(ms[i]);
    }
}

void swapRows(matrix m, int i1, int i2) {
    assert(m.nRows > i1);
    assert(m.nRows > i2);

    int *t = m.values[i1];
    m.values[i1] = m.values[i2];
    m.values[i2] = t;
}

void swapColumns(matrix m, int j1, int j2) {
    assert(m.nCols > j1);
    assert(m.nCols > j2);

    for (int i = 0; i < m.nRows; i++) {
        int t = m.values[i][j1];
        m.values[i][j1] = m.values[i][j2];
        m.values[i][j2] = t;
    }
}

bool isSquareMatrix(matrix m) {
    if (m.nRows == m.nCols)
        return true;
    return false;
}

bool sameSizeMatrices(matrix m1, matrix m2) {
    if (m1.nRows == m2.nRows && m1.nCols == m2.nCols)
        return true;
    return false;
}

bool twoMatricesEqual(matrix m1, matrix m2) {
    if (sameSizeMatrices(m1, m2)) {
        for (int i = 0; i < m1.nRows; i++) {
            for (int j = 0; j < m1.nCols; j++) {
                if (m2.values[i][j] != m1.values[i][j])
                    return false;
            }
        }
        return true;
    }
    return false;
}

bool isEMatrix(matrix m) {
    if (!isSquareMatrix(m))
        return false;

    for (int rIndex = 0; rIndex < m.nRows; rIndex++) {
        for (int cIndex = 0; cIndex < m.nCols; ++cIndex) {
            if (rIndex == cIndex && m.values[rIndex][cIndex] != 1
                || rIndex != cIndex && m.values[rIndex][cIndex] != 0)
                return false;
        }
    }
    return true;
}

bool isSymmetricMatrix(matrix m) {
    if (isSquareMatrix(m)) {
        int i = 0;
        int j = 0;
        while (i < m.nRows && j < m.nCols) {
            while (i != j) {
                if (m.values[i][j] != m.values[j][i])
                    return false;
                i++;
            }
            j++;
        }
        return true;
    }
    return false;
}

void transposeSquareMatrix(matrix m) {
    assert(isSquareMatrix(m));
    int i = 0;
    int j = 0;
    while (i < m.nRows && j < m.nCols) {
        while (i != j) {
            int t = m.values[i][j];
            m.values[i][j] = m.values[j][i];
            m.values[j][i] = t;
            i++;
        }
        i = 0;
        j++;
    }
}


position getMinValuePos(matrix m) {
    int copyMin = m.values[0][0];
    position p = {0, 0};
    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            if (m.values[i][j] < copyMin) {
                copyMin = m.values[i][j];
                p.colIndex = j;
                p.rowIndex = i;
            }
        }
    }
    return p;
}

position getMaxValuePos(matrix m) {
    int copyMax = m.values[0][0];
    position p = {0, 0};
    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            if (m.values[i][j] > copyMax) {
                copyMax = m.values[i][j];
                p.colIndex = j;
                p.rowIndex = i;
            }
        }
    }
    return p;
}

void swapArray(int *m, int a, int b) {
    int t = m[a];
    m[a] = m[b];
    m[b] = t;
}

void insertionSortRowsMatrixByRowCriteria(matrix m, int (*criteria)(int *, int)) {
    int a[m.nRows];
    for (int i = 0; i < m.nRows; i++) {
        a[i] = criteria(m.values[i], m.nCols);
        for (int j = 0; j < i; j++) {
            if (a[j] > a[i]) {
                for (int k = i; k > j; k--) {
                    swapArray(a, k - 1, k);
                    swapRows(m, k - 1, k);
                }
            }
        }
    }
}

void createArray(int *a, matrix m, int rows, const int cols) {
    for (int i = 0; i < rows; i++) {
        a[i] = m.values[i][cols];
    }
}

void insertionSortColsMatrixByColCriteria(matrix m, int (*criteria)(int *, int)) {
    int a[m.nCols];
    int b[m.nRows];
    for (int i = 0; i < m.nCols; i++) {
        createArray(b, m, m.nRows, i);
        a[i] = criteria(b, m.nRows);
        for (int j = 0; j < i; j++) {
            if (a[j] > a[i]) {
                for (int k = i; k > j; k--) {
                    swapArray(a, k - 1, k);
                    swapColumns(m, k - 1, k);
                }
            }
        }
    }
}

matrix createMatrixFromArray(const int *a, int nRows, int nCols) {
    matrix m = createMatrix(nRows, nCols);
    int k = 0;
    for (int i = 0; i < nRows; i++)
        for (int j = 0; j < nCols; j++)
            m.values[i][j] = a[k++];

    return m;
}

matrix *createArrayOfMatrixFromArray(const int *values, size_t nMatrices, size_t nRows, size_t nCols) {
    matrix *ms = getMemArrayOfMatrices(nMatrices, nRows, nCols);

    int l = 0;
    for (int k = 0; k < nMatrices; k++)
        for (int i = 0; i < nRows; i++)
            for (int j = 0; j < nCols; j++)
                ms[k].values[i][j] = values[l++];

    return ms;
}