/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 13:57:20 by angavrel          #+#    #+#             */
/*   Updated: 2018/02/06 18:36:30 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

static inline int	is_sorted_array(t_lst *lst, size_t n)
{
	while (--n)
	{
		if (lst.value > lst->next.value)
			return (0);
		lst = lst->next;
	}
	return (1);
}



static inline void	display_usage(void)
{
	ft_putendl_fd("Usage: execute program with digits as arguments", 2);
	exit(1);
}


/*
void				pa(size_t n, size_t list_a[n], size_t list_b[n])
{
	// envoie la valeur vers b
	ft_memcpy(a, n - 1)
	ft_printf("%d", n);
}

void				pb(size_t n, size_t list_a[n], size_t list_b[n])
{
	ft_printf("%d", n);
}


** rotate array UP


static inline void	rotate_list_up(t_lst *this)
{
	if (this->n > 1)
		swap(this->list, this->list + 1, sizeof(size_t));
}

void				ra(t_lst *a, t_lst *b)
{
	rotate_list_up(a);
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

static inline void	checker(t_lst *a, t_lst *b, size_t n)
{
	char		*line;
	size_t		op_nb;
	size_t		i;
	static void (*op[NB_INSTRU])(t_lst**, t_lst**) = {&sa, &sb, &ss};/*, &pa, \
		&pb, &ra, &rb, &rr, &rra, &rrb, &rrr};*/
	static const char *command[NB_INSTRU] = {"sa", "sb", "ss"};/*, "pa", \
		"pb", "ra", "rb", "rr", "rra", "rrb", "rrr"};*/

	op_nb = 0;
	ft_printf("_______________________________\n");
	while (get_next_line(0, &line) > 0)
	{
		i = 0;
		while (i < 3)//NB_INSTRU)
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

static inline void	check_duplicate(size_t n, t_lst lst)
{
	t_lst	tmp;
	size_t	i;

	i = 0;
	while (n--)
	{
		i = n;
		tmp = lst.value;
		while (i--)
		{
			lst = lst->next;
			if (tmp == lst.value)
				display_usage();
		}
		++i;
	}
}


static inline t_lst	lst_create(int value)
{
	t_lst	lst;

	lst.value = value;
	lst->next = NULL;
	lst->prev = NULL;
}

// a revoir
static inline void	lst_add(t_lst *lst, int value)
{
	t_lst	tmp;

	tmp = lst_create();
	lst->prev->next = tmp;
	lst->prev = tmp;
}

static inline void	get_lst(char **av, size_t i)
{
	size_t			j;
	t_lst			a;
	t_lst			b;
	size_t			n;

	if (!(a = (t_lst)malloc(i * sizeof(t_lst))) \
			|| !(b = (t_lst)malloc(i * sizeof(t_lst))))
		return ;
	if (!(n = i))
		display_usage();
	i = 0;
	while (++i <= n)
	{
		j = 0;
		while (av[i][j])
		{
			if (!(ft_isdigit(av[i][j]) ||
				((j == 0) && (*av[i] == '-' || *av[i] == '+'))))
				display_usage();
			++j;
		}
		lst_add(&a, ft_atoi(av[i]));
	}
	//while(i < n)
	//	ft_printf("%zu\n", list_a[i++]);
	check_duplicate(n, a);
	ft_bzero(&b, sizeof(b));
	presort(&a, n);
	checker(&a, &b, n);
}

int					main(int ac, char **av)
{
	get_lst(av, ac - 1);
	return (0);
}
