/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 13:57:20 by angavrel          #+#    #+#             */
/*   Updated: 2018/02/07 16:10:59 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

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

static inline void	error_handler(size_t i)
{
	char	*error_message[4] = \
		{"Usage: execute program with digits as arguments", \
		"Failed to malloc, perhaps you should have used VLAs",
		"Duplicate Values are forbidden",
		"Please enter valid digits i.e : -5, 15, 0..."};
	ft_putendl_fd(error_message[i], 2);
	exit(1);
}

static inline void	checker(t_lst *a, t_lst *b, size_t n)
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
			if (*line && !ft_strcmp(command[i], line))
			{
				op[i++](&a, &b);
				++op_nb;
				break;
			}
			++i;
		}
	}
	if (!b && is_sorted_array(a, n))
		ft_printf("OK\n");
	else
		ft_printf("KO\n");
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


static inline t_lst	*lst_create(int value)
{
	t_lst	*lst;

	if (!(lst = malloc(sizeof(t_lst))))
		error_handler(1);
	lst->value = value;
	lst->next = NULL;
	lst->prev = NULL;
	return (lst);
}

/*
** create an empty node
** The node after the one that was the last is the newly created node
** The node after the newly created is the first one
** The node before the newly created is the former last one
** The node before the first is the newly created one
*/

static inline void	lst_add(t_lst *lst, int value)
{
	t_lst	*tmp;

	tmp = lst_create(value);
	lst->prev->next = tmp;
	tmp->next = lst;
	tmp->prev = lst->prev;
	lst->prev = tmp;

}

static inline void	get_lst(char **av, size_t i)
{
	t_lst			*a;
	t_lst			*b;
	size_t			n;
	size_t			j;
	int				list[i];

	if (!(a = malloc(i * sizeof(t_lst))) \
			|| !(b = malloc(i * sizeof(t_lst))))
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
	i = 0;
	while (i < n)
		lst_add(a, list[i++]);
	//while(i < n)
	//	ft_printf("%zu\n", list_a[i++]);
	check_duplicate(n, list);
	ft_bzero(&b, sizeof(b));
	presort(a, n, list);
	checker(a, b, n);
}

int					main(int ac, char **av)
{
	get_lst(av, ac - 1);
	return (0);
}
