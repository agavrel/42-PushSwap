#include "checker.h"

typedef struct  s_node {
    size_t key;
    int value;
}               t_node;

static inline void swap(void *a, void *b, size_t n)
{
    unsigned char t[n];

    memcpy(t, a, n);
    memcpy(a, b, n);
    memcpy(b, t, n);
}

static inline void shellSort(t_node arr[], size_t size)
{
    size_t gap = size / 2;
    t_node tmp;
    size_t j;
    size_t i;

    while (gap > 0)
    {
        i = gap;
        while (i < size)
        {
            tmp = arr[i];
            j = i;
            while (j >= gap && arr[j - gap].value > tmp.value)
            {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            arr[j] = tmp;
            ++i;
        }
        gap >>= 1;
    }
}

static inline size_t partition(t_node arr[], int left, int right)
{
    int pivot;
    int i;
    int j;

    pivot = arr[right].value;
    i = left;
    j = left;
    while (j < right)
    {
        if (arr[j].value <= pivot)
            swap(&arr[i++], &arr[j], sizeof(t_node));
        ++j;
    }
    swap(&arr[i], &arr[right], sizeof(t_node));
    return (i);
}

static inline void quickSortIterative (t_node arr[], int left, int right)
{
    int stack[right - left + 1];
    int top;
    int p;

    top = 0;
    stack[top] = left;
    stack[++top] = right;
    while (top >= 0)
    {
        right = stack[top--];
        left = stack[top--];
        p = partition(arr, left, right);
        if (p - 1 > left)
        {
            stack[++top] = left;
            stack[++top] = p - 1;
        }
        if (p + 1 < right)
        {
            stack[++top] = p + 1;
            stack[++top] = right;
        }
    }
}

static inline void shuffle(size_t n, int arr[])
{
    size_t      rng;
    size_t      i;
    int         tmp[n];
    int         tmp2[n];

    memcpy(tmp, arr, sizeof(int) * n);
    bzero(tmp2, sizeof(int) * n);
    srand(time(NULL));
    i = 0;
    while (i < n)
    {
        rng = rand() % (n - i);
        while (tmp2[rng] == 1)
            ++rng;
        tmp2[rng] = 1;
        arr[i] = tmp[rng];
        ++i;
    }
}

static inline int checkIfSorted(size_t arr[], size_t n)
{
    while (n-- > 1)
        if (arr[n] < arr[n - 1])
            return (0);
    return (1);
}

static inline void testInit(size_t size)
{
    t_node  node[size];
    size_t  sortedNode[size];
    size_t  i;
    int     value[size];

    /* generate list filled with random numbers between -size / 2 and size / 2 */
    i = 0;
    while (i < size)
    {
        value[i] = i - size / 2;
        ++i;
    }
    /* shuffle list */
    shuffle(size, value);

    /* set original index for each element of the array */
    i = 0;
    while (i < size)
    {
        node[i].value = value[i];
        node[i].key = i;
        ++i;
    }

    /* launch algo and time it */
    clock_t start, end;
    start = clock();
    if (size < 1000) // 2000 seems to be the size limit where introSort achieves better results then shellSort
        shellSort(node, size); //  // runs in about 0.34sd
    else
        quickSortIterative(node, 0, size - 1);
    end = clock();


    /* displaying result */
    i = 0;
    while (i < size)
    {
        printf("desired index: %zu ", i);
        printf("original index : %zu, value : %d\n", node[i].key, node[i].value);
        sortedNode[node[i].key] = i;
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

    /* displaying result */
    i = 0;
    while (i < size)
    {
        printf("desired index: %zu\n", sortedNode[i]);
        ++i;
    }

    printf("%d\n", checkIfSorted(sortedNode, size));


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
