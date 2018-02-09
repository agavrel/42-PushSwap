/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rev_rotate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 18:09:34 by angavrel          #+#    #+#             */
/*   Updated: 2018/02/09 17:40:40 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

static inline void	rev_rotate(t_lst **lst)
{
	if ((*lst)->prev)
		*lst = (*lst)->prev;
}

inline void			rra(t_lst **a, t_lst **b)
{
	if (*a)
		rev_rotate(a);
	(void)b;
}

inline void			rrb(t_lst **a, t_lst **b)
{
	(void)a;
	if (*b)
		rev_rotate(b);
}

inline void			rrr(t_lst **a, t_lst **b)
{
	if (*a)
		rev_rotate(a);
	if (*b)
		rev_rotate(b);
}
