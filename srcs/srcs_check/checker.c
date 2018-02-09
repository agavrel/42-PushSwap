/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 18:54:28 by angavrel          #+#    #+#             */
/*   Updated: 2018/02/09 15:47:39 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

static inline int	is_sorted_array(t_lst *lst, size_t n)
{
	while (--n)
	{
		if (lst->value > lst->next->value)
			return (0);
		lst = lst->next;
	}
	return (1);
}

static inline void	lst_display(t_lst *a, t_lst *b)
{
	t_lst *tmp_a = a;
	t_lst *tmp_b = b;
	size_t n;

	ft_printf("------ List A ------\n");
	n = 0;
	while (a)
	{
		ft_printf("[%zu] ------> %zu\n", n++, a->value);
		a = a->next;
		if (a == tmp_a)
			break;
	}
	ft_printf("------ List B ------\n");
	n = 0;
	while (b)
	{
		ft_printf("[%zu] ------> %zu\n", n++, b->value);
		b = b->next;
		if (b == tmp_b)
			break;
	}
}

inline void			checker(t_lst *a, t_lst *b, size_t n)
{
	char		*line;
	size_t		op_nb;
	size_t		i;
	static void (*op[NB_INSTRU])(t_lst**, t_lst**) = {&sa, &sb, &ss, &pa, \
		&pb, &ra, &rb, &rr, &rra, &rrb, &rrr};
	static const char *command[NB_INSTRU] = {"sa", "sb", "ss", "pa", \
		"pb", "ra", "rb", "rr", "rra", "rrb", "rrr"};

	op_nb = 0;
	ft_printf("_______________________________\n");
	while (get_next_line(0, &line) > 0)
	{
		i = 0;
		while (i < NB_INSTRU)
		{
			if (*line && !ft_strcmp(command[i], line) && ++op_nb)
			{
				op[i++](&a, &b);
				break;
			}
			++i;
		}
		lst_display(a, b);
	}

	(!b && is_sorted_array(a, n)) ? ft_printf("OK\n") : ft_printf("KO\n");
}
