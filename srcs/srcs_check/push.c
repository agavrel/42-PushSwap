/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 18:49:06 by angavrel          #+#    #+#             */
/*   Updated: 2018/02/07 23:01:06 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

static inline void  push_to_from(t_lst **to, t_lst **from)
{
	t_lst	*tmp;

	if (!*to)
	{
		*to = *from;
		(*to)->next = *to;
		(*to)->prev = *to;
	}
	else if (*to)
	{
		(*to)->next = *to;
		(*to)->prev->next = *to;
		*to = *from;
	}
	tmp = *from;
	*from = (*from == (*from)->next) ? NULL : (*from)->next;
	ft_putstr("a");
	if (*from)
	{
		(*from)->prev = tmp->prev;
			ft_putstr("a");
		(*from)->prev->next = *from;
	}
}

inline void			pa(t_lst **a, t_lst **b)
{
	if (*b)
		push_to_from(a, b);
}

inline void			pb(t_lst **a, t_lst **b)
{
	if (*a)
		push_to_from(b, a);
}

/*
** create an empty node
** The node after the one that was the last is the newly created node
** The node after the newly created is the first one
** The node before the newly created is the former last one
** The node before the first is the newly created one
*/
/*
static inline void	lst_add(t_lst *lst, int value)
{
	t_lst	*tmp;

	tmp = lst_create(value);
	if (!lst)
		lst = tmp;
	else
	{
		if (lst->prev)
			lst->prev->next = tmp;
		tmp->next = lst;
		tmp->prev = lst->prev;
		lst->prev = tmp;
	}
}
*/
