/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 13:57:20 by angavrel          #+#    #+#             */
/*   Updated: 2018/02/05 14:06:46 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

static inline int   checkIfSorted(size_t arr[], size_t n)
{
    while (n-- > 1)
        if (arr[n] < arr[n - 1])
            return (0);
    return (1);
}

static inline void	init_oper(int n, t_pai oper[n])
{
	oper[0] = (t_pai) {.key =  "sa", .f = &sa};
	oper[1] = (t_pai) {.key =  "ra", .f = &ra};
	oper[2] = (t_pai) {.key =  "rra", .f = &rra};

	oper[3] = (t_pai) {.key =  "sb", .f = &sb};
	oper[4] = (t_pai) {.key =  "rb", .f = &rb};
	oper[5] = (t_pai) {.key =  "rrb", .f = &rrb};

	oper[6] = (t_pai) {.key =  "pa", .f = &pa};
	oper[7] = (t_pai) {.key =  "pb", .f = &pb};

	oper[8] = (t_pai) {.key =  "ss", .f = &ss};
	oper[9] = (t_pai) {.key =  "rr", .f = &rr};
	oper[10] = (t_pai) {.key =  "rrr", .f = &rrr};

	oper[11] = (t_pai) {.key =  "@", .f = NULL};
}

int                 main(int ac, char **av)
{
	t_checker	env;
	t_pai		oper[12];
    size_t      lst_b[size];
    char		*line;
    size_t      op_nb;

	init_oper(12, &oper[12]);
	env.disp_color = 0;
	env.disp_stack = 0;
	get_list(&env, ac, av);
	if (env.disp_stack)
		print_piles(&env, 0);
    op_nb = 0;
	while (get_next_line(0, &line))
	{
		++op_nb;
		do_oper(&env, 12, &oper[12]);
		if (env.disp_stack)
			print_piles(&env, 1);
	}
    if (checkIfSorted(lst_a) && !lst_b)
    {
        ft_printf("OK\n");
    else
        ft_printf("KO\n");
}
