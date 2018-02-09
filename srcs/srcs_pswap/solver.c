/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 23:20:33 by angavrel          #+#    #+#             */
/*   Updated: 2018/02/09 16:26:08 by angavrel         ###   ########.fr       */
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

static inline void	push_tail(t_lst *lst, t_lst *b, size_t forward, size_t back)
{
	ft_putnbr(forward);
	if (forward < back)
	{
		while (forward--)
		{
			ft_putendl("ra");
			ft_putendl_fd("ra", 2);
			lst = lst->next;
		}
	}
	else
	{
		while (back--)
		{
			ft_putendl("rra");
			ft_putendl_fd("rra", 2);
			lst = lst->prev;
		}
	}
	pb(&lst, &b);
	ft_putendl("pb");
	ft_putendl_fd("pb", 2);
}

static inline void	get_direction(t_lst *lst, size_t *forward, size_t *back, \
										size_t *tmp)
{
	t_lst	*begin;

	begin = lst;
	while (lst->value != *tmp)
	{
		lst = lst->next;
		++*forward;
	}
	lst = begin;
	while (lst->value != *tmp)
	{
		lst = lst->prev;
		++back;
	}
}

inline void			solver(t_lst *a, t_lst *b, size_t n)
{
	size_t	tmp;
	size_t	forward;
	size_t	back;


	tmp = 0;
	while (!is_sorted_array(a, n))
	{
		while (tmp < n)
		{
			forward = 0;
			back = 0;
			if (a->value + 1 == a->next->value)
			{
				ft_putendl("sa");
				ft_putendl_fd("sa", 2);
				sa(&a, &b);
			}
			else
			{
				get_direction(a, &forward, &back, &tmp);
				push_tail(a, b, forward, back);
				++tmp;
			}
		}
		while (tmp--)
		{
			ft_putendl("pa");
			ft_putendl_fd("pa", 2);
		}
	}
}
