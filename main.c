#include <stdio.h>
#include <math.h>
#include <time.h>

#define SIZE 51

typedef struct  s_node {
    int key;
    int value;
}               t_node;

static inline void swap(t_node *a, t_node *b)
{
    t_node t = *a;
    *a = *b;
    *b = t;
}

static inline void insertionSort(t_node arr[]) {
    int j;
    int i;

    i = 1;
    while (i < SIZE)
    {
        j = i++;
        while (j > 0 && arr[j - 1].value > arr[j].value)
        {
            swap(&arr[j - 1], &arr[j]);
            --j;
        }
    }
}

static inline void maxHeapify(t_node arr[], int heapSize, int index) {
    int left = (index + 1) * 2 - 1;
    int right = (index + 1) * 2;
    int largest;

    largest = (left < heapSize && arr[left].value > arr[index].value) ? left : index;
    if (right < heapSize && arr[right].value > arr[largest].value)
        largest = right;
    if (largest != index)
    {
        swap(&arr[index], &arr[largest]);
        maxHeapify(arr, heapSize, largest);
    }
}

static inline void heapSort(t_node arr[]) {
    int heapSize;
    int p;
    int i;

    p = (SIZE - 1) / 2;
    while (p >= 0)
        maxHeapify(arr, SIZE, p--);
    heapSize = SIZE;
    i = SIZE - 1;
    while (i > 0)
    {
        swap(&arr[i--], &arr[0]);
        maxHeapify(arr, --heapSize, 0);
    }
}


static inline int partition(t_node arr[], int left, int right) {
    int pivot;
    int i;
    int j;

    pivot = arr[right].value;
    i = left;
    j = left;
    while (j < right)
    {
        if (arr[j].value <= pivot)
            swap(&arr[i++], &arr[j]);
        ++j;
    }
    swap(&arr[i], &arr[right]);
    return (i);
}

static inline void quickSortRecursive(t_node arr[], int left, int right)
{
    if (left < right)
    {
        int q = partition(arr, left, right);
        quickSortRecursive(arr, left, q - 1);
        quickSortRecursive(arr, q + 1, right);
    }
}

static inline void introSort(t_node arr[]) {
    int partitionSize = partition(arr, 0, SIZE - 1);

    if (partitionSize < 16)
        insertionSort(arr);
    else if (partitionSize > (log(SIZE) * 2))
        heapSort(arr);
    else
        quickSortRecursive(arr, 0, SIZE - 1);
}


int main()
{
    int value[SIZE] = { 1, 2, 6, 15, 5, 19, 54, 0, -3, 7, 31, 75, -8, -4, 3, 55, 54, 21, 8, -9, 999, 99, 777, 88, 82, 56, 64, 128, 256, 512, 2048, 9898, 7979, 351, -543, 544, 546, 79797, 494090, 644645, 4564, 89798, -456465, 7897900, 4564654, 45465585, 456444444, 4479, -6464, -128, -64};
    t_node node[SIZE];
    int i;

    i = 0;
    while (i < SIZE)
    {
        node[i].value = value[i];
        node[i].key = i;
        ++i;
    }

    clock_t start, end;
    float elapsed_time;

    start = clock();
    introSort(node); // runs in about 0.34sd
    end = clock();

    i = 0;
    while (i < SIZE)
    {
        printf("original index : %d, desired index: %d, value : %d\n", node[i].key, i, node[i].value);
        ++i;
    }

    elapsed_time = (float)(end - start) / (float)CLOCKS_PER_SEC;
    printf("Elapsed time: %f seconds\n", elapsed_time);

    return 0;
}
