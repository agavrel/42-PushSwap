/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 23:04:07 by angavrel          #+#    #+#             */
/*   Updated: 2018/02/11 22:25:28 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

static inline void	get_lst(char **av, size_t i, t_lst **a, t_lst **b)
{
	size_t			n;
	size_t			j;
	int				list[i];

	if (!(*a = malloc(i * sizeof(t_lst))) || !(*b = malloc(i * sizeof(t_lst))))
		error_handler(1);
	if (!(n = i))
		error_handler(0);
	i = 0;
	while (++i <= n)
	{
		j = 0;
		while (av[i][j])
		{
			if (!(ft_isdigit(av[i][j]) ||
				((j == 0) && (av[i][0] == '-' || av[i][0] == '+'))))
				error_handler(3);
			++j;
		}
		list[i - 1] = ft_atoi(av[i]);
	}
	*a = lst_new(n);
	check_duplicate(n, list);
	ft_bzero(b, sizeof(*b));
	presort(*a, n, list);
}

int					main(int ac, char **av)
{
	t_lst			*a;
	t_lst			*b;

	get_lst(av, ac - 1, &a, &b);
	solver(&a, &b, ac - 1);
	return (0);
}
