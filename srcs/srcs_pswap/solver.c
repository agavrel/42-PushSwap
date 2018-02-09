/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 23:20:33 by angavrel          #+#    #+#             */
/*   Updated: 2018/02/09 20:56:08 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

inline int			is_sorted_array(t_lst *lst, size_t n)
{
	while (--n)
	{
		if (lst->value > lst->next->value)
			return (0);
		lst = lst->next;
	}
	return (1);
}

static inline void	rotate_list(t_lst **a)
{
	size_t	forward;
	size_t	back;
	t_lst	*begin;

	forward = 1;
	back = 1;
	begin = *a;
	while (begin->value < begin->next->value && begin->next != *a)
	{
		++forward;
		begin = begin->next;
	}
	begin = (*a)->prev;
	++back;
	while (begin->value > begin->prev->value && begin != *a)
	{
		++back;
		begin = begin->prev;
	}
	//ft_dprintf(2, "%d %d\n\n", forward, back);
	if (forward > 1 || back > 2)
	{
		if (forward < back)
		{
			while (forward--)
			{
				ft_putendl("ra");
				ra(a, NULL);
				if ((*a)->value == (*a)->next->value + 1)
				{
					ft_putendl("sa");
					sa(a, NULL);
				}
			}
		}
		else
		{
			while (back--)
			{
				ft_putendl("rra");
				rra(a, NULL);
				if ((*a)->value == (*a)->next->value + 1)
				{
					ft_putendl("sa");
					sa(a, NULL);
				}
			}
		}
	}
	if ((*a)->value == (*a)->next->value + 1)
	{
		ft_putendl("sa");
		sa(a, NULL);
	}

}

static inline void	push_tail(t_lst **a, t_lst **b, size_t forward, size_t back)
{
	if (forward || back)
	{
		if (forward < back)
		{
			while (forward--)
			{
				ft_putendl("ra");
				ra(a, b);
			}
		}
		else
		{
			while (back--)
			{
				ft_putendl("rra");
				rra(a, b);
			}
		}
	}
	ft_putendl("pb");
	pb(a, b);
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

inline void			solver(t_lst **a, t_lst **b, size_t n)
{
	size_t	tmp;
	size_t	forward;
	size_t	back;

	tmp = 0;
	while (!is_sorted_array(*a, n))
	{
		forward = 0;
		back = 0;
		if ((*a)->value == (*a)->next->value + 1)
		{
			ft_putendl("sa");
			sa(a, b);
		}
		else
		{
			if (n > 10)
			{
				get_direction(*a, &forward, &back, tmp);
				push_tail(a, b, forward, back);
				++tmp;
			}
			else
				rotate_list(a);
		}
		getchar();
	}
	while (*b)
	{
		ft_putendl("pa");
		pa(a, b);
	}
}
