/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 17:58:25 by angavrel          #+#    #+#             */
/*   Updated: 2018/02/06 18:09:15 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

static inline void	rotate(t_lst **this)
{
	if ((*this)->next)
		*this = (*this)->next;
}

inline void			ra(t_lst **a, t_lst **b)
{
	rotate(a);
	(void)b;
}

inline void			rb(t_lst **a, t_lst **b)
{
	(void)a;
	rotate(b);
}

inline void			rr(t_lst **a, t_lst **b)
{
	rotate(a);
	rotate(b);
}
