/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 18:10:37 by angavrel          #+#    #+#             */
/*   Updated: 2018/02/08 19:52:13 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"
/*
static inline void swap(void *a, void *b, size_t n)
{
    unsigned char t[n];

    memcpy(t, a, n);
    memcpy(a, b, n);
    memcpy(b, t, n);
}
*/

/*
** Swap the following way:
** 2nd element takes address of first element and its links to last and 1st;
** 1st element takes address of second element and its links to 2nd and next;
*/

static inline void	swap_list(t_lst **lst)
{
	t_lst	*tmp;

	if ((*lst)->next)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		tmp->next = (*lst)->next;
		tmp->next->prev = tmp;
		(*lst)->prev = tmp->prev;
		tmp->prev = *lst;
		(*lst)->next = tmp;
		(*lst)->prev->next = *lst;
	}
}

inline void			sa(t_lst **a, t_lst **b)
{
	if (*a)
		swap_list(a);
	(void)b;
}

inline void			sb(t_lst **a, t_lst **b)
{
	(void)a;
	if (*b)
		swap_list(b);
}

inline void			ss(t_lst **a, t_lst **b)
{
	if (*a)
		swap_list(a);
	if (*b)
		swap_list(b);
}
