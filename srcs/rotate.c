/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 17:58:25 by angavrel          #+#    #+#             */
/*   Updated: 2018/02/09 17:40:35 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

static inline void	rotate(t_lst **this)
{
	if ((*this)->next)
		*this = (*this)->next;
}

inline void			ra(t_lst **a, t_lst **b)
{
	if (*a)
		rotate(a);
	(void)b;
}

inline void			rb(t_lst **a, t_lst **b)
{
	(void)a;
	if (*b)
		rotate(b);
}

inline void			rr(t_lst **a, t_lst **b)
{
	if (*a)
		rotate(a);
	if (*b)
		rotate(b);
}
