/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   presort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 17:31:14 by angavrel          #+#    #+#             */
/*   Updated: 2018/02/07 18:48:59 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

/*
** will replace value from the array with final index
*/

static inline void		swap(void *a, void *b, size_t n)
{
	unsigned char t[n];

	memcpy(t, a, n);
	memcpy(a, b, n);
	memcpy(b, t, n);
}

static inline void		shellsort(t_node arr[], size_t size)
{
	t_node tmp;
	size_t j;
	size_t i;
	size_t gap;

	gap = size / 2;
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

static inline size_t	partition(t_node arr[], int left, int right)
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

static inline void		quicksort(t_node arr[], int left, int right)
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

/*
** first loop set original index for each element of the array
** then will sort array depending on n's value.
** finally attribute the correct index.
*/

void					presort(t_lst *list, size_t n, int unsorted_list[n])
{
	size_t	i;
	t_node	node[n];
	t_lst	*tmp;

	i = 0;
	while (i < n)
	{
		node[i].value = unsorted_list[i];
		node[i].key = i;
		++i;
	}
	(n < 1000) ? shellsort(node, n) : quicksort(node, 0, n - 1);
	i = 0;
	while (n--)
	{
		ft_printf("value : %d, original index : %zu, desired index: %zu\n", \
			node[n].value, node[n].key, n);
		i = node[n].key;
		tmp = list;
		while (i-- > 0)
			tmp = tmp->next;
		tmp->value = n;
	}
}
