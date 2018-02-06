#include "libft.h"
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

typedef struct  s_node {
	size_t		key;
	int			value;
}               t_node;

typedef struct	s_lst
{
	size_t		value;
	void		*prev;
	void		*next;
}				t_lst;

void		presort(t_lst *list, size_t n);

void		ss(t_lst **a, t_lst **b);
void		ra(t_lst **a, t_lst **b);
void		rb(t_lst **a, t_lst **b);
void		sa(t_lst **a, t_lst **b);
void		sb(t_lst **a, t_lst **b);
void		rr(t_lst **a, t_lst **b);
void		rra(t_lst **a, t_lst **b);
void		rrb(t_lst **a, t_lst **b);
void		rrr(t_lst **a, t_lst **b);
void		pa(t_lst **a, t_lst **b);
void		pb(t_lst **a, t_lst **b);
