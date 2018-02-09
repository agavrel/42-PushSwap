/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 17:58:25 by angavrel          #+#    #+#             */
/*   Updated: 2018/02/09 23:33:53 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

static inline void	rotate(t_lst **lst)
{
	if ((*lst)->next)
		*lst = (*lst)->next;
}

inline void			ra(t_lst **a, t_lst **b)
{
	ft_putendl("ra");
	if (*a)
		rotate(a);
	(void)b;
}

inline void			rb(t_lst **a, t_lst **b)
{
	ft_putendl("rb");
	(void)a;
	if (*b)
		rotate(b);
}

inline void			rr(t_lst **a, t_lst **b)
{
	ft_putendl("rr");
	if (*a)
		rotate(a);
	if (*b)
		rotate(b);
}
