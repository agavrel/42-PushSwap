/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rev_rotate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 18:09:34 by angavrel          #+#    #+#             */
/*   Updated: 2018/02/09 23:34:22 by angavrel         ###   ########.fr       */
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
	ft_putendl("rra");
	if (*a)
		rev_rotate(a);
	(void)b;
}

inline void			rrb(t_lst **a, t_lst **b)
{
	ft_putendl("rrb");
	(void)a;
	if (*b)
		rev_rotate(b);
}

inline void			rrr(t_lst **a, t_lst **b)
{
	ft_putendl("rrr");
	if (*a)
		rev_rotate(a);
	if (*b)
		rev_rotate(b);
}
