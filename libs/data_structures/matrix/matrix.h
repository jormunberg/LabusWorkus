#ifndef UNTITLED_MATRIX_H
#define UNTITLED_MATRIX_H

#include <stdio.h>
#include <stdbool.h>

typedef struct matrix {
    int ** values ; // элементы матрицы
    int nRows ; // количество рядов
    int nCols ; // количество столбцов
    } matrix ;

typedef struct position {
    int rowIndex ;
    int colIndex ;
    } position ;

// размещает в динамической памяти матрицу размером nRows на nCols
// возвращает матрицу
matrix getMemMatrix(int nRows, int nCols);

// размещает в динамической памяти массив из nMatrices матриц размером nRows на nCols
// возвращает указатель на нулевую матрицу
matrix *getMemArrayOfMatrices(int nMatrices, int nRows, int nCols);

// освобождает память, выделенную под хранение матрицы m
void freeMemMatrix(matrix m);

// освобождает память, выделенную под хранение массива ms из nMatrices матриц
void freeMemMatrices(matrix *ms, int nMatrices);

// ввод матрицы m
void inputMatrix(matrix m);

// ввод массива из nMatrices матриц, хранящейся по адресу ms
void inputMatrices(matrix *ms, int nMatrices);

// вывод матрицы m
void outputMatrix(matrix m);

// вывод массива из nMatrices матриц, хранящейся по адресу ms
void outputMatrices(matrix *ms, int nMatrices);

// обмен строк с порядковыми номерами i1 и i2 в матрице m
void swapRows(matrix m, int i1, int i2);

// обмен колонок с порядковыми номерами j1 и j2 в матрице m
void swapColumns(matrix m, int j1, int j2);

// выполняет сортировку вставками строк
// матрицы m по неубыванию значения функции criteria применяемой для строк
void insertionSortRowsMatrixByRowCriteria(matrix m,
        int (*criteria)(int *, int));

// выполняет сортировку вставками
// столбцов матрицы m по неубыванию значения функции criteria применяемой для столбцов
void insertionSortColsMatrixByColCriteria(matrix m,
        int (*criteria)(int *, int));

// возвращает значение ’истина’, если матрица m является квадратной, ложь – в противном случае
bool isSquareMatrix(matrix m);

// возвращает значение ’истина’, если матрицы m1 и m2 равны, ложь – в противном случае
bool twoMatricesEqual(matrix m1, matrix m2);

// возвращает значение ’истина’, если матрица m является единичной, ложь – в противном случае
bool isEMatrix(matrix m);

// возвращает значение ’истина’, если матрица m является симметричной, ложь – в противном случае
bool isSymmetricMatrix(matrix m);

// транспонирует квадратную матрицу m
void transposeSquareMatrix(matrix m);

// возвращает позицию минимального элемента матрицы m
position getMinValuePos(matrix m);

// возвращает позицию максимального элемента матрицы m
position getMaxValuePos(matrix m);

matrix mulMatrices(matrix m1, matrix m2) {
    if (m1.nCols != m2.nRows) {
        fprintf(stderr, "matrices cannot be multiplied");
        exit(1);
    }

    matrix multiplicationMatrix = getMemMatrix(m1.nRows, m2.nCols);

    for (int indexRowM1 = 0; indexRowM1 < m1.nRows; indexRowM1++)
        for (int indexColM2 = 0; indexColM2 < m2.nCols; indexColM2++) {
            multiplicationMatrix.values[indexRowM1][indexColM2] = 0;
            for (int indexRowM2 = 0; indexRowM2 < m2.nRows; indexRowM2++)
                multiplicationMatrix.values[indexRowM1][indexColM2] +=
                        m1.values[indexRowM1][indexRowM2]
                        * m2.values[indexRowM2][indexColM2];
        }

    return (matrix) multiplicationMatrix;
}

void getSquareOfMatrixIfSymmetric(matrix *m) {
    if (isSquareMatrix(*m)) {
        *m = mulMatrices(*m, *m);
    }
}

//5
bool isUnique(long long *a, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 1; j < n - 1; j++) {
            if (a[i] == a[j])
                return false;
        }
    }
    return true;
}

long long getSum(int *a, int n) {
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        sum += a[i];
    }
    return sum;
}

void transposeIfMatrixHasEqualSumOfRows(matrix m) {
    int a[m.nRows];
    for (int i = 0; i < m.nRows; i++) {
        a[i] = getSum(m.values[i], m.nCols);
    }
    if (isUnique(a, m.nRows) == true)
        transposeSquareMatrix(m);
}

//6
bool isMutuallyInverseMatrices(matrix m1, matrix m2) {
    matrix m3 = mulMatrices(m1, m2);
    if (!isEMatrix(m3))
        return false;
    return true;
}

//7
int max(int a, int b) {
    return a > b ? a : b;
}

int getMaxElementFromDiagonal(matrix m, int iRow, int iCol) {
    int maxValue = m.values[iRow][iCol];
    while (iRow < m.nRows && iCol < m.nCols)
        maxValue = max(maxValue, m.values[iRow++][iCol++]);
    return maxValue;
}

long long findSumOfMaxesOfPseudoDiagonal(matrix m) {
    int sum = 0;
    for (int i = 1; i < m.nRows; i++) {
        sum += getMaxElementFromDiagonal(m, i, 0);
    }

    for (int j = 1; j < m.nCols; j++) {
        sum += getMaxElementFromDiagonal(m, 0, j);
    }
    return sum;
}

//8
int min(int a, int b) {
    return a < b ? b : a;
}

int getMinInArea(matrix m) {
    position minPos = getMaxValuePos(m);
    int minElement = m.values[minPos.rowIndex][minPos.colIndex];

    int jRight = minPos.colIndex;
    int jLeft = minPos.colIndex;
    for (int i = minPos.rowIndex - 1; i >= 0; i--) {
        jLeft = jLeft > 0 ? jLeft - 1 : jLeft;
        jRight = jRight < m.nCols ? jRight + 1 : jRight;
        minElement = min(getMin(&m.values[i][jLeft], jRight - jLeft), minElement);
    }
    return minElement;
}


void transposeMatrix(matrix m) {
    for (int i = 0; i < m.nRows; i++)
        for (int j = 0; j < m.nCols; i++)
            if (i == j)
                swap((int *) &m.values[i][j], (int *) &m.values[j][i]);
}

//9
float getDistance(int *a, int n) {
    double sum = 0;
    for (int i = 0; i < n; i++)
        sum += pow(a[i], 2);
    return sqrt(sum);
}

void swapF(float *a, float *b) {
    float temp = *b;
    *b = *a;
    *a = temp;
}

void insertionSortRowsMatrixByRowCriteriaF(matrix m, float (criteria)(int *, int)) {
    float criteriaArray[m.nRows];
    for (size_t i = 0; i < m.nRows; ++i)
        criteriaArray[i] = criteria(m.values[i], m.nCols);

    for (int i = 1; i < m.nRows; ++i) {
        int j = i;
        while (j > 0 && criteriaArray[j - 1] > criteriaArray[j]) {
            swapF(&criteriaArray[j - 1], &criteriaArray[j]);
            swapRows(m, j - 1, j);

            j--;
        }
    }
}

void sortByDistances(matrix m) {
    insertionSortRowsMatrixByRowCriteriaF(m, getDistance);
}

#endif