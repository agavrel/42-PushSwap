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
	size_t		n;
	size_t		*list;
}				t_lst;

typedef struct 	s_env
{
	size_t		n;
	t_lst		*a;
	t_lst		*b;
}				t_env;

void	presort(t_env *env);
