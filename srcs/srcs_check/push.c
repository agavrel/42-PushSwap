/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 18:49:06 by angavrel          #+#    #+#             */
/*   Updated: 2018/02/08 15:57:07 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

/*
** clean links from the popped item
*/

static inline t_lst	*pop(t_lst **this)
{
	t_lst	*tmp;

	tmp = *this;
	if ((*this)->next == *this)
		*this = NULL;
	else
	{
		(*this)->prev->next = (*this)->next;
		(*this)->next->prev = (*this)->prev;
		*this = (*this)->next;
	}
	tmp->prev = NULL;
	tmp->next = NULL;
	return (tmp);
}

static inline void	push(t_lst **this, t_lst *item)
{
	if (*this == NULL)
	{
		item->prev = item;
		item->next = item;
	}
	else
	{
		item->prev = (*this)->prev;
		item->next = (*this);
		(*this)->prev->next = item;
		(*this)->prev = item;
	}
	*this = item;
}

static inline void  push_from_to(t_lst **from, t_lst **to)
{
	t_lst	*item;

	item = pop(from);
	if (item)
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
