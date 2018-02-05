/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 13:57:20 by angavrel          #+#    #+#             */
/*   Updated: 2018/02/05 15:59:32 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

static inline int	is_sorted_array(size_t arr[], size_t n)
{
	while (n-- > 1)
		if (arr[n] < arr[n - 1])
			return (0);
	return (1);
}

static inline void	isplay_usage(void)
{
	ft_putendl_fd("Usage: execute program with digits as arguments", 2);
	exit(1);
}

void				a(int a)
{
	ft_printf("%d", a);
}

void				b(int a)
{
	ft_printf("%d", a);
}

void				c(void)
{
	void(*w[2])(int) = {&a, &b};

	w[0](42);
}

static inline void	checker(size_t i, size_t list_a[i], size_t list_b[i])
{
	char		*line;
	size_t		op_nb;

	op_nb = 0;
	c();
	while (get_next_line(0, &line))
	{
		++op_nb;
	}
	if (is_sorted_array(list_a, i) && !list_b)
		ft_printf("OK\n");
	else
		ft_printf("KO\n");
}

static inline void	get_list(char **av, size_t i)
{
	size_t			lst_a[i];
	size_t			lst_b[i];
	size_t			j;
	const size_t	size = i;

	if (!size)
		display_usage();
	bzero(lst_a, sizeof(size_t) * size);
	while (i-- > 1)
	{
		j = 0;
		while (av[i][j])
		{
			if (!(ft_isdigit(av[i][j]) ||
				((j == 0) && (av[i][j] == '-' || av[i][j] == '+'))))
				display_usage();
			++j;
		}
		lst_a[i] = ft_atoi(av[i]);
	}
	bzero(lst_b, sizeof(size_t) * size);
	checker(size, lst_a, lst_b);
}

int					main(int ac, char **av)
{
	get_list(av, ac - 1);
}
