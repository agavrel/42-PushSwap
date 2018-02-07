/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 18:10:37 by angavrel          #+#    #+#             */
/*   Updated: 2018/02/07 22:44:28 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"
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
** 2nd element takes address of first element
** 1st element takes address of second element
**
**
*/
static inline void	swap_list(t_lst **this)
{
	t_lst	*memory_addresses[4];

	if ((*this)->next)
	{
		memory_addresses[0] = (*this)->prev;
		memory_addresses[1] = *this;
		memory_addresses[2] = ((*this)->next);
		memory_addresses[3] = (*this)->next->next;

		*this = memory_addresses[2];
		(*this)->next = memory_addresses[1];
		(*this)->prev = memory_addresses[0];
		(*this)->prev->next = memory_addresses[2];
		(*this)->next->next = memory_addresses[3];
		(*this)->next->prev = memory_addresses[2];
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
