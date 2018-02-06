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
	size_t		*value;
	void		*prev;
	void		*next;
}				t_lst;

void		presort(t_lst *list, size_t n);

inline void	sa(t_lst **a, t_lst **b);
inline void	sb(t_lst **a, t_lst **b);
inline void	ss(t_lst **a, t_lst **b);
inline void	ra(t_lst **a, t_lst **b);
inline void	rb(t_lst **a, t_lst **b);
inline void	rr(t_lst **a, t_lst **b);
inline void	rra(t_lst **a, t_lst **b);
inline void	rrb(t_lst **a, t_lst **b);
inline void	rrr(t_lst **a, t_lst **b);
inline void	pa(t_lst **a, t_lst **b);
inline void	pb(t_lst **a, t_lst **b);
