/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 18:49:06 by angavrel          #+#    #+#             */
/*   Updated: 2018/02/09 17:40:45 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

/*
** clean links from the popped item
*/

static inline t_lst	*pop(t_lst **lst)
{
	t_lst	*tmp;

	tmp = *lst;
	if ((*lst)->next == *lst)
		*lst = NULL;
	else
	{
		(*lst)->prev->next = (*lst)->next;
		(*lst)->next->prev = (*lst)->prev;
		*lst = (*lst)->next;
	}
	tmp->prev = NULL;
	tmp->next = NULL;
	return (tmp);
}

static inline void	push(t_lst **lst, t_lst *item)
{
	if (*lst == NULL)
	{
		item->prev = item;
		item->next = item;
	}
	else
	{
		item->prev = (*lst)->prev;
		item->next = (*lst);
		(*lst)->prev->next = item;
		(*lst)->prev = item;
	}
	*lst = item;
}

static inline void  push_from_to(t_lst **from, t_lst **to)
{
	t_lst	*item;

	if ((item = pop(from)))
		push(to, item);
}

inline void			pa(t_lst **a, t_lst **b)
{
	if (*b)
		push_from_to(b, a);
}

inline void			pb(t_lst **a, t_lst **b)
{
	if (*a)
		push_from_to(a, b);
}
