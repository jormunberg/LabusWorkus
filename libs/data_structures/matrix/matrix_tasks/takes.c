#include "takes.h"

void swapMinAndMaxRows(matrix m) {
    position min = getMinValuePos(m);
    position max = getMaxValuePos(m);
    swapRows(m, min.rowIndex, max.rowIndex);
}

int getMax(int *a, int n) {
    int max = a[0];
    for (int i = 1; i < n; ++i) {
        if (a[i] > max)
            max = a[i];
    }
    return max;
}

void sortRowsByMinElement(matrix m) {
    insertionSortRowsMatrixByRowCriteria(m, getMax);
}

int getMin(int *a, int n) {
    int min = a[0];
    for (int i = 1; i < n; ++i) {
        if (a[i] < min)
            min = a[i];
    }
    return min;
}

void sortColsByMinElement(matrix m) {
    insertionSortColsMatrixByColCriteria(m, getMin);
}

matrix mulMatrices(matrix m1, matrix m2) {
    assert(m1.nCols == m2.nRows);
    matrix m3 = createMatrix(m1.nRows, m2.nCols);
    for (int i = 0; i < m3.nRows; i++)
        for (int j = 0; j < m3.nCols; j++) {
            m3.values[i][j] = 0;
            for (size_t k = 0; k < m1.nCols; k++)
                m3.values[i][j] += m1.values[i][k] * m2.values[k][j];
        }
    return m3;
}

void getSquareOfMatrixIfSymmetric(matrix *m) {
    if (isSquareMatrix(*m) && isSymmetricMatrix(*m)) {
        *m = mulMatrices(*m, *m);
    }
}

long long getSum(int *a, int n) {
    long long sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += a[i];
    }
    return sum;
}

bool isUnique(long long *a, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (a[i] == a[j])
                return false;
        }
    }
    return true;
}

void transposeIfMatrixHasNotEqualSumOfRows(matrix m) {
    long long b[m.nRows];
    for (int i = 0; i < m.nRows; ++i) {
        b[i] = getSum(m.values[i], m.nCols);
    }
    if (isUnique(b, m.nRows)) {
        transposeSquareMatrix(m);
    }
}


bool isMutuallyInverseMatrices(matrix m1, matrix m2) {
    if (m1.nRows != m2.nRows || m1.nCols != m2.nCols)
        return false;

    matrix m = mulMatrices(m1, m2);

    return isEMatrix(m);
}

int max_(int a, int b) {
    return a < b ? b : a;
}

long long sumArray(int *a, size_t size) {
    int sum = 0;
    for (int i = 0; i < size; ++i) {
        sum += a[i];
    }
    return sum;
}

long long findSumOfMaxesOfPseudoDiagonal(matrix m) {
    int arraySize = m.nRows + m.nCols - 2;
    int max[arraySize];
    int i = 0;
    for (int j = 1; j < m.nRows; ++j) {
        max[i] = m.values[j][0];
        for (int k = j, x = 0; k < m.nRows && x < m.nCols; ++k, ++x) {
            max[i] = max_(max[i], m.values[k][x]);
        }
        i++;
    }
    for (int j = 1; j < m.nCols; ++j) {
        max[i] = m.values[0][j];
        for (int k = 0, x = j; k < m.nRows && x < m.nCols; ++k, ++x) {
            max[i] = max_(max[i], m.values[k][x]);
        }
        i++;
    }

    return sumArray(max, arraySize);
}

int min_(int a, int b) {
    return a < b ? a : b;
}

int getMinInArea(matrix m) {
    position max = getMaxValuePos(m);
    int min = m.values[max.rowIndex][max.colIndex];
    for (int k = 1; k < max.rowIndex; ++k) {
        for (int i = max.rowIndex - 1; i >= 0; --i) {
            int left;
            if (max.colIndex - k < 0)
                left = 0;
            else
                left = max.colIndex - k;
            int right;
            if (max.colIndex + k >= m.nCols)
                right = m.nCols - 1;
            else
                right = max.colIndex + k;
            while (left <= right) {
                min = min_(min, m.values[i][left]);
                left++;
            }
        }
    }

    return min;
}


void selectionSort(int *a, const size_t n) {
    if (n > 1) {
        for (int k = 0; k < n; k++) {
            int min = a[k];
            int count = k;
            for (int i = k; i < n; i++) {
                if (a[i] < min) {
                    min = a[i];
                    count = i;
                }
            }
            a[count] = a[k];
            a[k] = min;
        }
    }
}

int countNUnique(int *a, int n) {
    selectionSort(a, n);
    int count = 1;
    for (int i = 0; i < n - 1; i++) {
        if (a[i] != a[i + 1])
            count++;
    }
    return count;
}

int countEqClassesByRowsSum(matrix m) {
    long long a[m.nRows];
    for (int i = 0; i < m.nRows; ++i) {
        a[i] = 0;
    }
    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            a[i] += m.values[i][j];
        }
    }
    return countNUnique(a, m.nRows);
}

void matrixColumnsInArray(matrix m, int *a, int cols) {
    for (int i = 0; i < m.nRows; ++i) {
        a[i] = m.values[i][cols];
    }
}

int maxArray_(int *a, size_t n, int *position) {
    int max = a[0];
    for (int i = 1; i < n; ++i) {
        if (a[i] > max) {
            max = a[i];
            *position = i;
        }
    }
    return max;
}

long long sumArray_(int *a, size_t size, int positionMaxRows) {
    int sum = 0;
    for (int i = 0; i < size; ++i) {
        if (i != positionMaxRows)
            sum += a[i];
    }
    return sum;
}

int getNSpecialElement(matrix m) {
    int a[m.nRows];
    int positionMaxRows;
    int countSpecialElement = 0;
    for (int i = 0; i < m.nCols; ++i) {
        matrixColumnsInArray(m, a, i);
        int max = maxArray_(a, m.nRows, &positionMaxRows);
        long long sum = sumArray_(a, m.nRows, positionMaxRows);
        if (max > sum)
            countSpecialElement++;
    }
    return countSpecialElement;
}

position getLeftMin(matrix m) {
    position pMin = {0, 0};
    int min = m.values[0][0];
    for (int i = 0; i < m.nRows; ++i) {
        for (int j = 0; j < m.nCols; ++j) {
            if (min > m.values[i][j]) {
                min = m.values[i][j];
                pMin.rowIndex = i;
                pMin.colIndex = j;
            }
        }
    }
    return pMin;
}

void swapPenultimateRow(matrix m) {
    position pMin = getLeftMin(m);
    for (int i = m.nCols - 1; i >= 0; --i) {
        m.values[m.nRows - 2][i] = m.values[i][pMin.colIndex];
    }
}

bool isNonDescendingSorted(int *a, int n) {
    for (int i = 0; i < n - 1; ++i) {
        if (a[i] > a[i + 1])
            return false;
    }
    return true;
}

bool hasAllNonDescendingRows(matrix m) {
    for (int i = 0; i < m.nRows; ++i) {
        if (!isNonDescendingSorted(m.values[i], m.nCols))
            return false;
    }
    return true;
}

int countNonDescendingRowsMatrices(matrix *ms, int nMatrix) {
    int countNonDescending = 0;
    for (int i = 0; i < nMatrix; ++i) {
        if (hasAllNonDescendingRows(ms[i]))
            countNonDescending++;
    }
    return countNonDescending;
}

int countZeroRows(matrix m) {
    int zeroRows = 0;
    for (int i = 0; i < m.nRows; ++i) {
        int zero = 0;
        for (int j = 0; j < m.nCols; ++j) {
            if (m.values[i][j] == 0)
                zero++;
        }
        if (zero == m.nCols)
            zeroRows++;
    }
    return zeroRows;
}

void printMatrixWithMaxZeroRows(matrix *ms, int nMatrix) {
    int zeroRows[nMatrix];
    for (int i = 0; i < nMatrix; ++i) {
        zeroRows[i] = countZeroRows(ms[i]);
    }
    int max = getMax(zeroRows, nMatrix);
    for (int i = 0; i < nMatrix; ++i) {
        if (zeroRows[i] == max)
            outputMatrix(ms[i]);
    }
}

int maxMatrix(matrix m) {
    int max = m.values[0][0];
    for (int i = 0; i < m.nRows; ++i) {
        for (int j = 0; j < m.nCols; ++j) {
            max = max_(max, m.values[i][j]);
        }
    }
    return max;
}

void printMatrixWithMinMax(matrix *ms, int nMatrix) {
    int max[nMatrix];
    for (int i = 0; i < nMatrix; ++i) {
        max[i] = maxMatrix(ms[i]);
    }
    int min = getMin(max, nMatrix);
    for (int i = 0; i < nMatrix; ++i) {
        if (max[i] == min)
            outputMatrix(ms[i]);
    }
}

float getDistance(int *a, int n) {
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += a[i] * a[i];
    }
    return sqrt(sum);
}

void universalSwap(void *a, void *b, size_t size) {
    char *a1 = a;
    char *b1 = b;
    for (int i = 0; i < size; i++) {
        char t = *a1;
        *a1 = *b1;
        *b1 = t;

        a1++;
        b1++;
    }
}

void insertionSortRowsMatrixByRowCriteriaFloat(matrix m, float (*criteria)(int *, int)) {
    float *rows = (float *) malloc(sizeof(float) * m.nRows);
    for (int rIndex = 0; rIndex < m.nRows; ++rIndex)
        rows[rIndex] = criteria(m.values[rIndex], m.nCols);

    for (int rIndex = 1; rIndex < m.nRows; ++rIndex) {
        int curIndex = rIndex;
        while (curIndex > 0 && rows[curIndex] < rows[curIndex - 1]) {
            swapRows(m, curIndex, curIndex - 1);
            universalSwap(&rows[curIndex], &rows[curIndex - 1], sizeof(int));
            curIndex--;
        }
    }
}

void sortByDistances(matrix m) {
    insertionSortRowsMatrixByRowCriteriaFloat(m, getDistance);
}