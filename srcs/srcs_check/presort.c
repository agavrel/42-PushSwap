/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   presort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 17:31:14 by angavrel          #+#    #+#             */
/*   Updated: 2018/02/06 15:40:23 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

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

void	presort(size_t *list, size_t n)
{
	size_t	i;
	t_node	node[n];
	//size_t  sortedNode[env->n];

	/* set original index for each element of the array */
	i = 0;
	while (i < n)
	{
		node[i].value = list[i];
		node[i].key = i;
		++i;
	}
	if (n < 1000)
		shellSort(node, n);
	else
		quickSortIterative(node, 0, n - 1);

	/* displaying result */
	i = 0;
	while (i < n)
	{
		printf("desired index: %zu ", i);
		printf("original index : %zu, value : %d\n", node[i].key, node[i].value);
		list[node[i].key] = i;
		++i;
	}
}
