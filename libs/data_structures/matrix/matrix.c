#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "matrix.h"

// размещает в динамической памяти матрицу размером nRows на nCols
// возвращает матрицу
matrix getMemMatrix(int nRows, int nCols) {
    int **values = (int **) malloc(sizeof(int *) * nRows);
    for (int i = 0; i < nRows; i++)
        values[i] = (int *) malloc(sizeof(int) * nCols);
    return (matrix) {values, nRows, nCols};
}

// размещает в динамической памяти массив из nMatrices матриц размером nRows на nCols
// возвращает указатель на нулевую матрицу
matrix *getMemArrayOfMatrices(int nMatrices, int nRows, int nCols) {
    matrix *m = (matrix *) malloc(sizeof(matrix) * nMatrices);
    for (int i = 0; i < nMatrices; i++)
        m[i] = getMemMatrix(nRows, nCols);
    return m;
}

// освобождает память, выделенную под хранение матрицы m
void freeMemMatrix(matrix m) {
    for (int i = 0; i < m.nRows; i++)
        free(m.values[i]);
    free(m.values);
}

// освобождает память, выделенную под хранение массива ms из nMatrices матриц
void freeMemMatrices(matrix *ms, int nMatrices) {
    for (int i = 0; i < nMatrices; i++)
        freeMemMatrix(ms[i]);
    free(ms);
}

// ввод матрицы m
void inputMatrix(matrix m) {
    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            scanf("%d", &m.values[i][j]);
        }
    }
}

// ввод массива из nMatrices матриц, хранящейся по адресу ms
void inputMatrices(matrix *ms, int nMatrices) {
    for (int i = 0; i < nMatrices; i++)
        inputMatrix(ms[i]);
}

// вывод матрицы m
void outputMatrix(matrix m) {
    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++)
            printf("%d ", m.values[i][j]);
        printf("\n");
    }
}

// вывод массива из nMatrices матриц, хранящейся по адресу ms
void outputMatrices(matrix *ms, int nMatrices) {
    for (int i = 0; i < nMatrices; i++) {
        outputMatrix(ms[i]);
        printf("\n");
    }
}

void swap(int a, int b) {
    int t = a;
    a = b;
    b = t;
}


// обмен строк с порядковыми номерами i1 и i2 в матрице m
void swapRows(matrix m, int i1, int i2) {
    swap((int *) &m.values[i1], (int *) &m.values[i2]);
}

// обмен колонок с порядковыми номерами j1 и j2 в матрице m
void swapColumns(matrix m, int j1, int j2) {
    for (int i = 0; i < m.nRows; i++) {
        swap(&m.values[i][j1], &m.values[i][j2]);
    }
}

// выполняет сортировку вставками строк
// матрицы m по неубыванию значения функции criteria применяемой для строк
void insertionSortRowsMatrixByRowCriteria(matrix m,
                                          int (*criteria)(int *, int)) {
    int arrayOfCriteria[m.nRows];
    for (int i = 0; i < m.nRows; i++) {
        arrayOfCriteria[i] = criteria(m.values[i], m.nCols);
    }
    for (int j = 1; j < m.nRows; j++) {
        int k = j;
        while (k != 0 && arrayOfCriteria[k - 1] > arrayOfCriteria[k]) {
            swapRows(m, k - 1, k);
            swap(&arrayOfCriteria[k - 1], &arrayOfCriteria[k]);
            k--;
        }
    }
}

// выполняет сортировку вставками
// столбцов матрицы m по неубыванию значения функции criteria применяемой для столбцов
void insertionSortColsMatrixByColCriteria(matrix m,
                                          int (*criteria)(int *, int)) {
    int arrayOfCriteria[m.nCols];
    for (int i = 0; i < m.nCols; i++) {
        int arrayRow[m.nRows];
        for (int j = 0; j < m.nRows; j++) {
            arrayRow[j] = m.values[i][j];
        }
        arrayOfCriteria[i] = criteria(arrayRow, m.nRows);
    }

    for (int j = 1; j < m.nCols; j++) {
        int k = j;
        while (k != 0 && arrayOfCriteria[k - 1] > arrayOfCriteria[k]) {
            swapRows(m, k - 1, k);
            swap(&arrayOfCriteria[k - 1], &arrayOfCriteria[k]);
            k--;
        }
    }
}

// возвращает значение ’истина’, если матрица m является квадратной, ложь – в противном случае
bool isSquareMatrix(matrix m) {
    if (m.nRows == m.nCols) {
        return true;
    } else {
        return false;
    }
}

// возвращает значение ’истина’, если матрицы m1 и m2 равны, ложь – в противном случае
bool twoMatricesEqual(matrix m1, matrix m2) {
    if (m1.nRows != m2.nRows || m1.nCols != m2.nCols) {
        return false;
    } else {
        for (int i = 0; i < m1.nRows; i++) {
            for (int j = 0; j < m1.nCols; j++) {
                if (m1.values[i][j] != m2.values[i][j]) {
                    return false;
                }
            }
        }
    }
    return true;
}

// возвращает значение ’истина’, если матрица m является единичной, ложь – в противном случае
bool isEMatrix(matrix m) {
    if (isSquareMatrix(m) == false) {
        return false;
    }
    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            if ((i != j && m.values[i][j] != 0) || (i == j && m.values[i][j] != 1))
                return false;
        }
    }
    return true;
}

// возвращает значение ’истина’, если матрица m является симметричной, ложь – в противном случае
bool isSymmetricMatrix(matrix m) {
    if (isSquareMatrix(m) == false) {
        return false;
    }
    for (int i = 0; i < m.nRows; i++)
        for (int j = 0; j < m.nCols; i++)
            if (m.values[i][j] != m.values[j][i])
                return false;
    return true;
}

// транспонирует квадратную матрицу m
void transposeSquareMatrix(matrix m) {
    if (isSquareMatrix(m)) {
        for (int i = 0; i < m.nRows; i++)
            for (int j = 0; j < m.nCols; i++)
                if (i == j)
                    swap((int *) &m.values[i][j], (int *) &m.values[j][i]);
    }
}

// возвращает позицию минимального элемента матрицы m
position getMinValuePos(matrix m) {
    int minValue = m.values[0][0];
    position minPos = {0, 0};
    for (int i = 0; i < m.nRows; i++) {
        for (int j = 1; j < m.nCols; i++) {
            if (m.values[i][j] < minValue) {
                minValue = m.values[i][j];
                minPos.colIndex = j;
                minPos.rowIndex = i;
            }
        }
    }
    return minPos;
}

// возвращает позицию максимального элемента матрицы m
position getMaxValuePos(matrix m) {
    int maxValue = m.values[0][0];
    position maxPos = {0, 0};
    for (int i = 0; i < m.nRows; i++) {
        for (int j = 1; j < m.nCols; i++) {
            if (m.values[i][j] > maxValue) {
                maxValue = m.values[i][j];
                maxPos.colIndex = j;
                maxPos.rowIndex = i;
            }
        }
    }
    return maxPos;
}

void swapRowsOfMinAndMax(matrix m) {
    position max = getMaxValuePos(m);
    position min = getMinValuePos(m);

    swapRows(m, max.rowIndex, min.rowIndex);
}

int getMax(const int *a, int n){
    int maxValue = a[0];
    for(int i = 1; i < n; i++)
        if( a[i] > maxValue)
            maxValue = a[i];
    return maxValue;
}

void sortRowsByMaxElement(matrix m) {
    insertionSortRowsMatrixByRowCriteria(m, getMax);
}

int getMin(const int *a, int n){
    int minValue = a[0];
    for(int i = 1; i < n; i++)
        if( a[i] < minValue)
            minValue = a[i];
    return minValue;
}

void sortColsByMinElement(matrix m) {
    insertionSortColsMatrixByColCriteria(m, getMin);
}