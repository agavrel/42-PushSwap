/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 23:20:33 by angavrel          #+#    #+#             */
/*   Updated: 2018/02/18 22:34:49 by angavrel         ###   ########.fr       */
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

/*
** checks the most suitable way to swap elems
*/

static inline int	should_we_swap(t_lst **a, t_lst **b)
{
	if (*b && (*b)->next)
	{
		if ((*a)->next->value < (*a)->value)
		{
			(*b)->next->value < (*b)->value ? ss(a, b) : sa(a, NULL);
			return (1);
		}
		else if ((*b)->next->value < (*b)->value)
		{
			sb(NULL, b);
			return (1);
		}

	}
	else if ((*a)->next->value < (*a)->value)
	{
		sa(a, NULL);
		return (1);
	}
	return (0);
}

/*
** checks the most suitable way to rotate elems
*/
/*
static inline int	rev_rotate_opti(t_lst **a, t_lst **b)
{
	if (*b && (*b)->prev)
	{
		if ((*a)->prev->value > (*a)->value)
		{
			(*b)->prev->value > (*b)->value ? rrr(a, b) : rra(a, NULL);
			return (1);
		}
		else if ((*b)->prev->value > (*b)->value)
		{
			rrb(NULL, b);
			return (1);
		}
	}
	if ((*a)->prev->value > (*a)->value)
	{
		rra(a, NULL);
		return (1);
	}
	return (0);
}
*/
/*
static inline int	rotate_opti(t_lst **a, t_lst **b)
{
	if (*b && (*b)->next)
	{
		if ((*a)->prev->value > (*a)->value)
		{
			(*b)->prev->value > (*b)->value ? rr(a, b) : ra(a, NULL);
			return (1);
		}
		else if ((*b)->prev->value > (*b)->value && (*b)->next->next != *b)
		{
			rb(NULL, b);
			return (1);
		}
	}
	if ((*a)->next->value > (*a)->value)
	{
		ra(a, NULL);
		return (1);
	}
	return (0);
}
*/
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


static void quick_sort_pb(t_lst **a, t_lst **b, size_t min, size_t max)
{
	while (min < max / 2)
	{
		//ft_dprintf(2, "heey 2\n");

	//	ft_dprintf(2, "%zu, %zu, %zu\n", (*a)->value, n / 2, n_b);
	ft_dprintf(2, "if (%zu > %zu), ++%zu and pb\n", (*a)->value, max / 2, min);
		if ((*a)->value > max / 2 && ++min)
		{
			pb(a, b);
			getchar();
	//		ft_dprintf(2, "heey 3\n");
		}
		if (!should_we_swap(a, b))
			rotate_opti(a, b);

		getchar();
	}
}

static void quick_sort_pa(t_lst **a, t_lst **b, size_t min, size_t max)
{
	while (min >= max / 4)
	{
		ft_dprintf(2, "mmgdgfdgdfm if (%zu > %zu), ++%zu and pb\n", (*a)->value, max / 2, min);
//		getchar();
		if ((*b)->value <= (double)(max * 0.75) && min--)
			pa(a, b);
		if (!should_we_swap(a, b))
			rotate_opti(a, b);
	}
}
*/static void recusive_quick_sort_b(t_lst **a, t_lst **b, size_t max, size_t min);

void recusive_quick_sort(t_lst **a, t_lst **b, size_t max, size_t min)
{
	size_t nb;
	size_t size;
	size_t current_max;

	size = max - min;
	nb = size / 2 + 1; // +1 ?
	current_max = nb;
	//getchar();
	ft_dprintf(2, "Start of quicksort : test min %lu max %lu nb %lu other %lu\n", min, max, nb, (size) / 2 + min);
	getchar();
	while (nb)
	{
	//	ft_dprintf(2, "list a test min %lu max %lu nb %lu other %lu\n", min, max, nb, (size) / 2 + min);
	//	getchar();

		if ((*a)->value <= size / 2 + min) // median
		{
			//ft_dprintf(2, "test min %lu max %lu\n", min, max);
			pb(a, b);
			nb--;
		}
		else
		{//getchar();
			if ((*a)->value == current_max)
			{
				ra(a, NULL);
				current_max++;
			}
			else if (!should_we_swap(a, b))
				ra(a, NULL);
		}

	}

//	ft_dprintf(2, "list a test min %lu max %lu nb %lu other %lu\n", min, max, nb, (size) / 2 + min);
	recusive_quick_sort_b(a, b, max, size / 2 + min);
	getchar();
	if (max >= min)
		recusive_quick_sort(a, b, size / 2 + min, min);
}

static void recusive_quick_sort_b(t_lst **a, t_lst **b, size_t max, size_t min)
{
	size_t size;
	size_t nb;
	size_t current_max;

	size = max - min;
	nb = min;
	current_max = 1;
	while (*b)
	{
		if ((*b)->value == nb)
		{
			pa(a, b);
			--nb;
		}
		else if (nb == (*b)->value - 1 && current_max >= 1)
		{
			pa(a, b);
			--nb;
			--current_max;
		}
		else if (nb == (*b)->value + 1 && current_max <= 1)
		{
			pa(a, b);
			--nb;
			++current_max;
		}
		else if (!should_we_swap(a, b))
			rb(a, b);
		ft_dprintf(2, "%zu %zu %zu\n", nb, max, min);
	}
	if (max >= min)
		recusive_quick_sort_b(a, b, max, size / 2 + min);
	recusive_quick_sort(a, b, size / 2 + min, min);
}
/*
static inline void	recusive_quick_sort(t_lst **a, t_lst **b, size_t min, size_t max)
{
	//size_t		n_b;

	if (min == 1 || max == 1)
		return ;
	getchar();
	//ft_dprintf(2, "heyyy if (%zu > %zu), n_b = %zu n_begin = %zu and pa\n", (*a)->value, n / 4, n_b, nbegin);
	//getchar();
	recusive_quick_sort(a, b, min / 4, max / 2);
	recusive_quick_sort(a, b, 0, max / 4);
}*/
/*

static void	recusive_quick_sort(t_lst **a, t_lst **b, size_t min, size_t max)
{
	division de la liste en deux sur liste b
	rec2(); seconde fonction de recursion que ne fait que push la liste b dans a par strats de n / 2
	rec(); rapel de la fonction pour la partie restante de la liste a;
}
rec2 s'arrete quand plus ren sur la liste b;
rec est recursif jusqu'a ce qu'il y ai plus qu'un element // un ou plutot 3


*/



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
	if (n == 31)
		solver_large(a, b, n);
	else if (n < 10)
		solver_tiny(a, b, n);
	else if (n < 100)
		solver_small(a, b, n);
	else if (n < 110)
		solver_medium(a, b, n);
	else
		solver_large(a, b, n);
}
