#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <stdlib.h> // rand function

typedef struct  s_node {
    size_t key;
    int value;
}               t_node;

static inline void swap(t_node *a, t_node *b)
{
    t_node t = *a;
    *a = *b;
    *b = t;
}

static inline void shellSort(t_node arr[], size_t size)
{
    size_t gap = size / 2;
    int tmp;
    size_t j;
    size_t i;

    while (gap > 0)
    {
        i = gap;
        while (i < size)
        {
            tmp = arr[i].value;
            j = i;
            while (j >= gap && arr[j - gap].value > tmp)
            {
                arr[j].value = arr[j - gap].value;
                j -= gap;
            }
            arr[j].value = tmp;
            ++i;
        }
        gap >>= 1;
    }
}

static inline void insertionSort(t_node arr[], size_t size)
{
    size_t j;
    size_t i;
    t_node tmp;

    i = 1;
    while (i < size)
    {
        j = i++;
        tmp = arr[j];
        while (j > 0 && arr[j - 1].value > tmp.value)
            --j;
        memmove(&arr[j + 1], &arr[j], sizeof(t_node) * (i - j - 1));
        swap(&arr[j], &tmp);
    }
}

static inline void maxHeapify(t_node arr[], size_t heapSize, size_t index)
{
    const size_t right = (index + 1) * 2;
    size_t left;
    size_t largest;

    left = right - 1;
    largest = (left < heapSize && arr[left].value > arr[index].value) ? left : index;
    if (right < heapSize && arr[right].value > arr[largest].value)
        largest = right;
    if (largest != index)
    {
        swap(&arr[index], &arr[largest]);
        maxHeapify(arr, heapSize, largest);
    }
}

static inline void heapSort(t_node arr[], size_t size)
{
    size_t heapSize;
    int    p;
    size_t i;

    p = (size - 1) / 2;
    while (p >= 0)
        maxHeapify(arr, size, p--);
    heapSize = size;
    i = size - 1;
    while (i > 0)
    {
        swap(&arr[i--], &arr[0]);
        maxHeapify(arr, --heapSize, 0);
    }
}


static inline size_t partition(t_node arr[], size_t left, size_t right)
{
    int pivot;
    size_t i;
    size_t j;
//    int tmp;

    pivot = arr[right].value;
    i = left;
    j = left;
    while (j < right)
    {
        if (arr[j].value <= pivot)
            swap(&arr[i++], &arr[j]);
/*        tmp = (arr[j].value - pivot) >> 31;
        swap(&arr[(~tmp & i)], &arr[j]);
        i -= tmp; // equivalent to ++i if t = -1, else nothing happens. nb: useless good compilers will make the conditional move optimization */
        ++j;
    }
    swap(&arr[i], &arr[right]);
    return (i);
}

static inline void quickSortRecursive(t_node arr[], size_t left, size_t right)
{
    size_t q;

    if (left < right)
    {
        q = partition(arr, left, right);
        quickSortRecursive(arr, left, q - 1);
        quickSortRecursive(arr, q + 1, right);
    }
}

static inline void introSort(t_node arr[], size_t size)
{
    const size_t partitionSize = partition(arr, 0, size - 1);

    if (partitionSize < 16)
        insertionSort(arr, size);
    else if (partitionSize > (log(size) * 2))
        heapSort(arr, size);
    else
        quickSortRecursive(arr, 0, size - 1);
}

static inline void testInit(size_t size)
{
    t_node  node[size];
    t_node  node2[size];
    size_t  i;
    int     value[size];
    int     rng;

    /* generate list filled with random numbers */
    srand(time(NULL));
    i = 0;

    while (i < size)
    {
        rng = rand() % size;
        value[i] = (rng & 1) ? ~rng : rng;
        ++i;
    }

    /* set original index for each element of the array */
    i = 0;
    while (i < size)
    {
        node[i].value = value[i];
        node[i].key = i;
        ++i;
    }
    memcpy(node2, node, sizeof(t_node) * size);
    /* launch algo and time it */
    clock_t start, end, start2, end2;

    start = clock();
//    if (SIZE < 2000) // 2000 seems to be the size limit where introSort achieves better results then shellSort
        shellSort(node, size);
    end = clock();
//    else
    start2 = clock();
        introSort(node, size); // runs in about 0.34sd
    end2 = clock();

    /* displaying result */
    i = 0;
    while (i < size)
    {
        printf("original index : %zu, desired index: %zu, value : %d\n", node[i].key, i, node[i].value);
        ++i;
    }

    /* check that list is correctly sorted */
    int fail = 0;
    i = 1;
    while (i < size - 1)
    {
        if (node[i - 1].value > node[i].value || node[i].value > node[i + 1].value) {
            fail = 1; break;
        }
        i += 2;
    }
    printf(fail ? "FAIL\n" : "SUCCESS\n");

    /* micro-benchmarking time for algo */
    float elapsed_time = (float)(end - start) / (float)CLOCKS_PER_SEC;
    printf("Elapsed time for shellSort: %f seconds\n", elapsed_time);
    float elapsed_time2 = (float)(end2 - start2) / (float)CLOCKS_PER_SEC;
    printf("Elapsed time for introSort: %f seconds\n", elapsed_time2);
}

int main(int ac, char **av)
{
//    int value[SIZE] = { 1, 2, 6, 15, 5, 19, 54, 0, -3, 7, 31, 75, -8, -4, 3, 55, 54, 21, 8, -9, 999, 99, 777, 88, 82, 56, 64, 128, 256, 512, 2048, 9898, 7979, 351, -543, 544, 546, 79797, 494090, 644645, 4564, 89798, -456465, 7897900, 4564654, 45465585, 456444444, 4479, -6464, -128, -64};
    size_t  size;
    if (ac != 2)
        return (1);
    size = atoi(av[1]);
    if (size <= 0)
        return (1);
    testInit(size);
    return (0);
}
