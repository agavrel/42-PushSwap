/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 18:10:37 by angavrel          #+#    #+#             */
/*   Updated: 2018/02/06 18:10:39 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static inline void swap(void *a, void *b, size_t n)
{
    unsigned char t[n];

    memcpy(t, a, n);
    memcpy(a, b, n);
    memcpy(b, t, n);
}

inline void			swap_list(t_lst **this)
{
	t_lst	*tmp;

	if ((*this)->next)
	{
		tmp = *this;
		*this = (*this)->next;
		(*this)->prev = tmp;
	}

}

inline void			sa(t_lst **a, t_lst **b)
{
	swap_list(a);
	(void)b;
}

inline void			sb(t_lst **a, t_lst **b)
{
	(void)a;
	swap_list(b);
}

inline void			ss(t_lst **a, t_lst **b)
{
	swap_list(a);
	swap_list(b);
}
