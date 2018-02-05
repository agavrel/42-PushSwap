/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 13:57:20 by angavrel          #+#    #+#             */
/*   Updated: 2018/02/05 17:48:46 by angavrel         ###   ########.fr       */
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

static inline void	display_usage(void)
{
	ft_putendl_fd("Usage: execute program with digits as arguments", 2);
	exit(1);
}

static inline void	swap_list(size_t *arr)
{
	(void)arr;
}

static inline void	sa(t_env *env)
{
	printf("hello");
	swap_list(env->a->list);
}

static inline void	sb(t_env *env)
{
	swap_list(env->b->list);
}

static inline void	ss(t_env *env)
{
	swap_list(env->a->list);
	swap_list(env->b->list);
}
/*
void				pa(size_t n, size_t list_a[n], size_t list_b[n])
{
	ft_printf("%d", n);
}

void				pb(size_t n, size_t list_a[n], size_t list_b[n])
{
	ft_printf("%d", n);
}

void				ra(size_t n, size_t list_a[n], size_t list_b[n])
{
	ft_printf("%d", n);
}

void				rb(size_t n, size_t list_a[n], size_t list_b[n])
{
	ft_printf("%d", n);
}


void				rr(t_env *env)
{
	ra(env->n, env->list_a);
	rb(env->n, env->list_b);
}


void				rra(size_t n, size_t list_a[n], size_t list_b[n])
{
	ft_printf("%d", n);
}

void				rrb(size_t n, size_t list_a[n], size_t list_b[n])
{
	ft_printf("%d", n);
}

void				rrr(size_t n, size_t list_a[n], size_t list_b[n])
{
	rra(n, list_a, list_b);
	rrb(n, list_a, list_b);
}
*/
#define NB_INSTRU 11

static inline void	checker(t_env *env)
{
	char		*line;
	size_t		op_nb;
	size_t		i;
	static void(*op[NB_INSTRU])(t_env *) = {&sa, &sb, &ss};/*, &pa, \
		&pb, &ra, &rb, &rr, &rra, &rrb, &rrr};*/
	const char *command[NB_INSTRU] = {"sa", "sb", "ss"};/*, "pa", \
		"pb", "ra", "rb", "rr", "rra", "rrb", "rrr"};*/

	op_nb = 0;
	while (get_next_line(0, &line))
	{
		i = 0;
		while (i < NB_INSTRU)
		{
			if (ft_strequ(command[i], line))
				op[i](env);
			++i;
		}
		++op_nb;
	}
	if (is_sorted_array(env->a->list, env->n) && !env->b->list)
		ft_printf("OK\n");
	else
		ft_printf("KO\n");
}

/*
** initialize list_a and list_b
*/

static inline void	get_lst(char **av, size_t i)
{
	size_t			list_a[i];
	size_t			list_b[i];
	size_t			j;
	t_env			env;

	if (!(env.n = i))
		display_usage();
	bzero(list_a, sizeof(t_lst) * env.n);
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
		list_a[i] = ft_atoi(av[i]);
	}
	bzero(list_b, sizeof(size_t) * env.n);
	env.a->list = list_a;
	env.b->list = list_b;
	presort(&env);
	checker(&env);
}

int					main(int ac, char **av)
{
	get_lst(av, ac - 1);
}
