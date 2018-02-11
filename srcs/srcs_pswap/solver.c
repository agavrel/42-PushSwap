/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 23:20:33 by angavrel          #+#    #+#             */
/*   Updated: 2018/02/11 23:32:28 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

static inline size_t	count_unsorted_elem(t_lst *lst)
{
	t_lst	*begin;
	size_t	i;

	begin = lst;
	i = 0;
	while (lst->next != begin)
	{
		if (lst->value > lst->next->value)
			++i;
		lst = lst->next;
	}
	//ft_dprintf(2, "i : %zu\n", i);
	return (i);
}

static inline void	get_direction(t_lst *lst, size_t *forward, size_t *back, \
										size_t tmp)
{
	t_lst	*begin;

	begin = lst;
	while (lst->value != tmp)
	{
		lst = lst->next;
		++*forward;
	}
	lst = begin;
	while (lst->value != tmp)
	{
		lst = lst->prev;
		++*back;
	}
}
/*
static inline void	get_direction2(t_lst *lst, size_t *forward, size_t *back)
{
	t_lst	*begin;

	begin = lst;
	while (begin->value < begin->next->value && begin->next != lst)
	{
		++*forward;
		begin = begin->next;
	}
	begin = lst->prev;
	++*back;
	while (begin->value > begin->prev->value && begin != lst)
	{
		++*back;
		begin = begin->prev;
	}
}
*/
/*
** will overflow to SIZE_MAX if j = i + 1;
*/

static inline int	adj_num(size_t i, size_t j)
{
	i -= j;
	return (i == SIZE_MAX || i == 1);
}
/*
static inline void analyze_list(t_lst **a, size_t n, \
									size_t forward, size_t back)
{
	get_direction2(*a, &forward, &back);
	ft_dprintf(2, "%d %d\n\n", forward, back);
	if (forward <= back)
	{
		while (forward--)
		{
			ra(a, NULL);
			if (((*a)->value == (*a)->next->value + 1) || \
			(n > 2 && (*a)->value == n - 1 && (*a)->next->next->value == n - 2))
				sa(a, NULL);
		}
	}
	else
	{
		while (back--)
		{
			rra(a, NULL);
			if ((*a)->value == (*a)->next->value + 1)
				sa(a, NULL);
		}
	}
	if ((*a)->value == (*a)->next->value + 1)
		sa(a, NULL);
	else if (n > 2 && (*a)->value == 0 && ((*a)->next->value == n - 1))
		sa(a, NULL);
}
*/

// 6 operations:  4 3 1 0 2       0 2 4 3 1
// 7 operations: 4 0 3 2 1   pb pb rr ss pa pa ra -> can you do better ? need to implement it

static inline void should_we_swap(t_lst **a, t_lst **b)
{
	if (*b && (*b)->next)
	{
		if ((*a)->next->value < (*a)->value)
			(*b)->next->value < (*b)->value ? ss(a, b) : sa(a, NULL);
		else if ((*b)->next->value < (*b)->value)
				sb(NULL, b);
	}
	if ((*a)->next->value < (*a)->value)
		sa(a, NULL);
}

static inline void push_items(t_lst **a, t_lst **b, size_t nb)
{
	while (nb > 0)
	{
		pb(a, b);
		--nb;
	}
	rr(a, b);
	should_we_swap(a, b);
}

static inline void	solver_tiny(t_lst **a, t_lst **b, size_t n)
{
	int		value;
	size_t	nb;
	size_t	i;

	i = n >> 1;
	value = 0;
	while ((*a)->value == 0 || *b || !is_sorted_lst(*a))
	{
		if ((nb = count_unsorted_elem(*a)) > n / 2)
			push_items(a, b, (n + 1) / nb);
		while (((*a)->next->value == 0 && (*a)->value == n - 1) || \
			((*a)->prev->value + 1 == (*a)->value))
			ra(a, NULL);
		/*if (((*a)->value == (*a)->next->value + 1) \
			|| ((*a)->next->value == n - 1 && (*a)->value == 0))
				sa(a, NULL);*/
		while (((*a)->value == (*a)->next->value + 1) || \
			((*a)->prev->value == 0 && (*a)->value > n >> 1)
			|| (((*a)->value == (*a)->prev->prev->value + 1)
			&& adj_num((*a)->prev->prev->value, (*a)->prev->value)))
				rra(a, NULL);
		if ((*a)->value == 0)
		{
			*a = (*a)->next;
			while (i)
			{
				value += (*a)->value;
				*a = (*a)->next;
				--i;
			}
			while (i < n >> 1)
			{
				value -= (*a)->value;
				*a = (*a)->next;
				++i;
			}
			if (value >= 0)
				pb(a, b);
		}
		while (*b && (((*a)->value == (*b)->value + 1) || ((*a)->value == 0 &&
		 	(*b)->value == n - 1)))
			pa(a, b);
	}
}

static inline void	push_tail(t_lst **a, t_lst **b, size_t forward, size_t back)
{
	if (forward || back)
	{
		if (forward < back)
		{
			while (forward--)
				ra(a, b);
		}
		else
			while (back--)
				rra(a, b);
	}
	pb(a, b);
}

/*
** selection sorting
*/

static inline void	solver_small(t_lst **a, t_lst **b, size_t n)
{
	size_t	tmp;
	size_t	forward;
	size_t	back;

	tmp = 0;
	if (((*a)->value == (*a)->next->value + 1) \
		|| ((*a)->next->value == n - 1 && (*a)->value == 0))
		sa(a, NULL);
	//ft_dprintf(2, "hey%zu   %zu\n", (*a)->value , (*a)->next->value);
	while (!is_sorted_lst(*a))
	{
		if (!(*a)->next->next->next)
			break;
			//ft_dprintf(2, "gergergerg\n");
		forward = 0;
		back = 0;
		get_direction(*a, &forward, &back, tmp);
		push_tail(a, b, forward, back);
		++tmp;
		getchar();//
	}
	if ((*a)->value == (*a)->next->value + 1)
		sa(a, NULL);
	while (*b)
		pa(a, b);
		//ft_dprintf(2, "a %zu a1 %zu \n", (*a)->value, (*a)->next->value);
}

/*
** insertsort
*/

static inline void	solver_medium(t_lst **a, t_lst **b, size_t n)
{
	while (!is_sorted_lst(*a))
	{
		(void)b;
		(void)n;
	}
}


/*
static inline void	fill_b(t_lst **a, t_lst **b, size_t n)
{
	while (n_b < n / 2)
	{
		should_we_swap(a, b);
		if ((*a)->value >= n / 2 && ++n_b)
			pb(a, b);
		else
			ra(a, b);
	}
}

static inline void	fill_a(t_lst **a, t_lst **b, size_t n)
{
	while (n_b > n / 4)
	{
		should_we_swap(a, b);
		if ((*b)->value >= n / 4 && (*b)->value <= n / 2 && n_b--)
			pa(a, b);
	}
}
*/
static inline void	recusive_quick_sort(t_lst **a, t_lst **b, size_t n, size_t nbegin)
{
	size_t		n_b;

	n_b = 0;
	if (is_sorted_lst(*a) && !*b)
		return ;
	while (n_b < n / 2 && n_b >= nbegin)
	{
		//ft_dprintf(2, "heey 2\n");
		should_we_swap(a, b);
	//	ft_dprintf(2, "%zu, %zu, %zu\n", (*a)->value, n / 2, n_b);
		if ((*a)->value >= n / 2 && ++n_b)
		{
			pb(a, b);
	//		ft_dprintf(2, "heey 3\n");
		}

		else
			ra(a, b);
	}
	while (n_b > n / 4 && n_b < nbegin)
	{
		should_we_swap(a, b);
		if ((*b)->value >= n / 4 && (*b)->value <= n / 2 && n_b--)
			pa(a, b);
	}
	recusive_quick_sort(a, b, n / 2, n / 2);
	recusive_quick_sort(a, b, n / 2, 0);
}

/*
** quicksort
*/

static inline void	solver_large(t_lst **a, t_lst **b, size_t n)
{

//	while (!is_sorted_lst(*a))
// /	{
		recusive_quick_sort(a, b, n, 0);
//	}
	while (*b)
		pa(a, b);
}

inline void			solver(t_lst **a, t_lst **b, size_t n)
{
	if (n < 10)
		solver_tiny(a, b, n);
	else if (n < 100)
		solver_small(a, b, n);
	else if (n < 110)
		solver_medium(a, b, n);
	else
		solver_large(a, b, n);
}
