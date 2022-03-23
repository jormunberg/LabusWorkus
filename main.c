#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdint.h>

#define TIME_TEST(testCode, time){ \
clock_t start_time = clock () ; \
testCode \
clock_t end_time = clock () ;\
clock_t sort_time = end_time - start_time ; \
time = ( double ) sort_time / CLOCKS_PER_SEC ; \
}

#define ARRAY_SIZE(a) sizeof(a) / sizeof(a[0])

void outputArray_(int *arr, int size) {
    for (int i = 0; i < size; ++i) {
        printf("%d", arr[i]);
    }
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int digit(int n, int k, int N, int M) {
    return (n >> (N * k) & (M - 1));
}

//обменная сортировка
void bubbleSort(int *a, size_t size) {
    for (size_t i = 0; i < size - 1; i++)
        for (size_t j = size - 1; j > i; j--)
            if (a[j - 1] > a[j])
                swap(&a[j - 1], &a[j]);
}

//сортировка выбором
void selectionSort(int *a, const size_t size) {
    for (int i = 0; i < size - 1; i++) {
        int minPos = i;
        for (int j = i + 1; j < size; j++)
            if (a[j] < a[minPos])
                minPos = j;
        swap(&a[i], &a[minPos]);
    }
}

//сортировка вставками
void insertionSort(int *a, const size_t size) {
    for (size_t i = 1; i < size; i++) {
        int t = a[i];
        int j = i;
        while (j > 0 && a[j - 1] > t) {
            a[j] = a[j - 1];
            j--;
        }
        a[j] = t;
    }
}

//сортировка расческой
void combSort(int *a, const size_t size) {
    size_t step = size;
    int swapped = 1;
    while (step > 1 || swapped) {
        if (step > 1)
            step /= 1.24733;
        swapped = 0;
        for (size_t i = 0, j = i + step; j < size; ++i, ++j)
            if (a[i] > a[j]) {
                swap(&a[i], &a[j]);
                swapped = 1;
            }
    }
}

//сортировка Шелла
void shellSort(int *a, const size_t size) {
    for (int step = size / 2; step > 0; step /= 2) {
        for (size_t i = step; i < size; i++) {
            int t = a[i];
            int j = i;
            while (j - step >= 0 && a[j - step] > t) {
                a[j] = a[j - step];
                j -= step;
            }
            a[j] = t;
        }
    }
}

//цифровая сортировка
void radixSort_(int *a, int *n) {
    int bit = 8;
    int k = (32 + bit - 1) / bit;
    int M = 1 << bit;
    int sz = n - a;
    int *b = (int *) malloc(sizeof(int) * sz);
    int *c = (int *) malloc(sizeof(int) * M);
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < M; j++)
            c[j] = 0;

        for (int *j = a; j < n; j++)
            c[digit(*j, i, bit, M)]++;

        for (int j = 1; j < M; j++)
            c[j] += c[j - 1];

        for (int *j = n - 1; j >= a; j--)
            b[--c[digit(*j, i, bit, M)]] = *j;

        int cur = 0;
        for (int *j = a; j < n; j++)
            *j = b[cur++];
    }
    free(b);
    free(c);
}

void radixSort(int *a, size_t n) {
    radixSort_(a, a + n);
}

typedef struct SortFunc {
    void (*sort)(int *arr, int size);

    char arr[64];
} SortFunc;

typedef struct GeneratingFunc {
    void (*generate)(int *arr, int size);

    char arr[64];
} GeneratingFunc;

void generateOrderedArray(int *a, int size) {
    for (int i = 0; i < size; ++i) {
        a[i] = i;
    }
}

void generateOrderedBackwards(int *a, int size) {
    for (int i = 0; i < size; ++i) {
        a[i] = size - i;
    }
}

void generateRandomArray(int *a, int size) {
    for (int i = 0; i < size; ++i) {
        a[i] = rand() % 100000;
    }
}

double getTime() {
    clock_t start_time = clock();

    clock_t end_time = clock();
    clock_t sort_time = end_time - start_time;
    return (double) sort_time / CLOCKS_PER_SEC;
}

bool isOrdered(int *arr, int size) {
    for (int i = 1; i < size; ++i) {
        if (arr[i] < arr[i - 1])
            return false;
    }
    return true;
}

void checkTime(void (*sortFunc)(int *, int), void (*generateFunc)(int *, int), int size, char *experimentName) {
    static int runCounter = 1;
    static int innerBuffer[1000000];
    generateFunc(innerBuffer, size);
    printf("Run #%d| ", runCounter++);
    printf("Name : %s\n", experimentName);

    double time;
    TIME_TEST({ sortFunc(innerBuffer, size); }, time)
//результаты замера
    printf(" Status : ");
    if (isOrdered(innerBuffer, size)) {
        printf("OK! Time: %.3f s.\n", time);
//запись в файл
        char filename[256];
        sprintf(filename, "./data/%s.csv", "experiment");
        FILE *f = fopen(filename, "a");
        if (f == NULL) {
            printf("FileOpenError %s", filename);
            exit(1);
        }
        fprintf(f, "%zu; %.3f\n", size, time);
        fclose(f);
    } else {
        printf("Wrong !\n");

//вывод массива, который не смог быть отсортирован
        outputArray_(innerBuffer, size);
        exit(1);
    }
}

void timeExperiment() {
//описание функций сортировки
    SortFunc sorts[] = {
            //{selectionSort, "selectionSort"},
            //{insertionSort, "insertionSort"},
            //{shellSort, "shellSort"},
           {bubbleSort, "bubbleSort"},
           // {combSort, "combSort"},
           // {radixSort, "radixSort"}
    };
    const unsigned FUNCS_N = ARRAY_SIZE(sorts);

//функции генерации
    GeneratingFunc generatingFuncs[] = {
            {generateRandomArray, "random"} ,
            //{generateOrderedArray, "ordered"},
            //{generateOrderedBackwards, "orderedBackwards"}
    };
    const unsigned CASES_N = ARRAY_SIZE(generatingFuncs);

//запись результатов в файл
    for (int size = 10000; size <= 100000; size += 10000) {
        printf("-----------------------------------------------------\n");
        printf(" Size : %d\n", size);
        for (int i = 0; i < FUNCS_N; i++) {
            for (int j = 0; j < CASES_N; j++) {
//генерация имени файла
                static char filename[128];
                sprintf(filename, "%s_%s_time ", sorts[i].arr, generatingFuncs[j].arr);
                checkTime(sorts[i].sort, generatingFuncs[j].generate, size, filename);
            }
        }
        printf("\n");
    }
}

int main() {
    timeExperiment();
    return 0;
}