
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
        swap(&arr[index], &arr[largest], sizeof(t_node));
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
        swap(&arr[i--], &arr[0], sizeof(t_node));
        maxHeapify(arr, --heapSize, 0);
    }
}

static inline void merge(t_node arr[], int left, int m, int right)
{
    int i, j, k;
    int n1 = m - left + 1;
    int n2 =  right - m;

    /* create temp arrays */
    t_node L[n1], R[n2];

    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = left; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if (L[i].value <= R[j].value)
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    /* Copy the remaining elements of L[], if there
       are any */
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    /* Copy the remaining elements of R[], if there
       are any */
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

/* l is for left index and r is right index of the
   sub-array of arr to be sorted */
static inline void mergeSort(t_node arr[], size_t left, size_t right)
{
    int m;

    if (left < right)
    {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        m = left + (right - left) / 2;

        // Sort first and second halves
        mergeSort(arr, left, m);
        mergeSort(arr, m + 1, right);
        merge(arr, left, m, right);
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
        swap(&arr[j], &tmp, sizeof(t_node));
    }
}
 
