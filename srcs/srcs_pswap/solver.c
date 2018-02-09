/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 23:20:33 by angavrel          #+#    #+#             */
/*   Updated: 2018/02/09 18:56:51 by angavrel         ###   ########.fr       */
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
			get_direction(*a, &forward, &back, tmp);
			push_tail(a, b, forward, back);
			++tmp;
		}
	}
	while (*b)
	{
		ft_putendl("pa");
		pa(a, b);
	}
}
