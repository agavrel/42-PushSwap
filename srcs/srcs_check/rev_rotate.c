/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rev_rotate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 18:09:34 by angavrel          #+#    #+#             */
/*   Updated: 2018/02/06 18:13:55 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static inline void	rev_rotate(t_lst **this)
{
	if ((*this)->previous)
		*this = (*this)->previous;
}

inline void			rra(t_lst **a, t_lst **b)
{
	rev_rotate(a);
	(void)b;
}

inline void			rrb(t_lst **a, t_lst **b)
{
	(void)a;
	rev_rotate(b);
}

inline void			rrr(t_lst **a, t_lst **b)
{
	rev_rotate(a);
	rev_rotate(b);
}
