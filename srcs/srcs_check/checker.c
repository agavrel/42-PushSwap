/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 18:54:28 by angavrel          #+#    #+#             */
/*   Updated: 2018/02/18 22:18:31 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

static inline void	lst_display(t_lst *a, t_lst *b)
{
	t_lst *tmp_a = a;
	t_lst *tmp_b = b;
	size_t n;

	ft_dprintf(2, "_______________________________\n");
	ft_dprintf(2, "------ List A ------\n");
	n = 0;
	while (a)
	{
		ft_dprintf(2, "[%zu]               %zu\n", n++, a->value);
		a = a->next;
		if (a == tmp_a)
			break;
	}
	ft_dprintf(2, "------ List B ------\n");
	n = 0;
	while (b)
	{
		ft_dprintf(2, "[%zu]               %zu\n", n++, b->value);
		b = b->next;
		if (b == tmp_b)
			break;
	}
	ft_dprintf(2, "_______________________________\n");
}

inline void			checker(t_lst *a, t_lst *b)
{
	char		*line;
	size_t		op_nb;
	size_t		i;
	static void (*op[NB_INSTRU])(t_lst**, t_lst**) = {&sa, &sb, &ss, &pa, \
		&pb, &ra, &rb, &rr, &rra, &rrb, &rrr};
	static const char *command[NB_INSTRU] = {"sa", "sb", "ss", "pa", \
		"pb", "ra", "rb", "rr", "rra", "rrb", "rrr"};

	op_nb = 0;
	lst_display(a, b);
	while (get_next_line(0, &line) > 0)
	{
		i = 0;
		while (i < NB_INSTRU)
		{
			if (*line && !ft_strcmp(command[i], line) && ++op_nb)
			{
				op[i](&a, &b);
				ft_dprintf(2, "\e[1;34m%s\e[0m\n", command[i]);
				lst_display(a, b);
				ft_dprintf(2, "\e[1;34mNB --> %d\e[0m\n", op_nb);
				break;
			}
			++i;
		}
	}
	(!b && is_sorted_lst(a)) ? ft_printf("OK\n") : ft_printf("KO\n");
}
