/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 18:49:06 by angavrel          #+#    #+#             */
/*   Updated: 2018/02/07 18:55:32 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

static inline void  push_to_from(t_lst **to, t_lst **from)
{
	if (from == NULL)
		return ;
	(*from)->prev->next = (*from)->next;
	(*from)->next->prev = (*from)->prev;
	(*from)->prev = (*to)->prev;
	(*from)->next = *to;
	(*to)->prev->next = *from;
	(*to)->prev = *from;
	from = to;
	to = &(*to)->next;
}

inline void			pa(t_lst **a, t_lst **b)
{
	push_to_from(a, b);
}

inline void			pb(t_lst **a, t_lst **b)
{
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
