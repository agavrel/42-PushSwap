/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 23:04:07 by angavrel          #+#    #+#             */
/*   Updated: 2018/02/09 18:09:52 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

inline void			error_handler(size_t i)
{
	const static char	*error_message[4] = \
		{"Usage: execute program with digits as arguments", \
		"Failed to malloc, perhaps you should have used VLAs",
		"Duplicate Values are forbidden",
		"Please enter valid digits i.e : -5, 15, 0..."};
	ft_putendl_fd(error_message[i], 2);
	exit(1);
}

/*
** initialize list_a and list_b
** then ensure there is no duplicate in list_a
*/

static inline void	check_duplicate(size_t n, int lst[n])
{
	int		tmp;
	size_t	i;

	i = 0;
	while (n--)
	{
		i = n;
		tmp = lst[i];
		while (i--)
			if (lst[i] == tmp)
				error_handler(2);
	}
}

static inline t_lst	*lst_create()
{
	t_lst	*lst;

	if (!(lst = malloc(sizeof(t_lst))))
		error_handler(1);
	lst->value = 0;
	lst->next = NULL;
	lst->prev = NULL;
	return (lst);
}

static inline t_lst *lst_new(size_t n)
{
	t_lst	*lst;
	t_lst	*tmp;

	lst = lst_create();
	tmp = lst;
	while (--n)
	{
		lst->next = lst_create();
		lst->next->prev = lst;
		lst = lst->next;
	}
	tmp->prev = lst;
	lst->next = tmp;
	return (lst);
}

static inline void	get_lst(char **av, size_t i)
{
	t_lst			*a;
	t_lst			*b;
	size_t			n;
	size_t			j;
	int				list[i];

	if (!(a = malloc(i * sizeof(t_lst))) || !(b = malloc(i * sizeof(t_lst))))
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
				((j == 0) && (*av[i] == '-' || *av[i] == '+'))))
				error_handler(3);
			++j;
		}
		list[i - 1] = ft_atoi(av[i]);
	}

	a = lst_new(n);
	check_duplicate(n, list);
	ft_bzero(&b, sizeof(b));
	presort(a, n, list);
	solver(&a, &b, n);
}

int					main(int ac, char **av)
{
	get_lst(av, ac - 1);
	return (0);
}
