/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 19:49:08 by angavrel          #+#    #+#             */
/*   Updated: 2018/02/09 18:09:20 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSHSWAP_H
# define PUSHSWAP_H

# include "libft.h"
# include <stdio.h>
# include <math.h>
# include <time.h>
# include <string.h>
# include <stdlib.h>

/*
** use for presorting array
*/

typedef struct		s_node {
	size_t			key;
	int				value;
}					t_node;

/*
** About double linked-list in C++ :
** https://cs.calvin.edu/activities/books/c++/
** intro/3e/WebItems/Ch14-Web/STL-List-14.4.pdf
*/

typedef struct		s_lst
{
	size_t			value;
	struct s_lst	*prev;
	struct s_lst	*next;
}					t_lst;

/*
** calculate final index in advance for each values
*/

void				presort(t_lst *list, size_t n, int unsorted_list[n]);

/*
** error handling using char array, faster than if else
*/

void				error_handler(size_t i);

/*
** check values
*/

void				checker(t_lst *a, t_lst *b, size_t n);

/*
** Solving Algo
*/

void				solver(t_lst **a, t_lst **b, size_t n);

/*
** check that lst is sorted by ascending order
*/

int					is_sorted_array(t_lst *lst, size_t n);

/*
** Instructions below, 'a' stands for list a, 'b' for list b and 's' for both
*/

# define NB_INSTRU 11

/*
** swap 2 first values
*/

void				sa(t_lst **a, t_lst **b);
void				sb(t_lst **a, t_lst **b);
void				ss(t_lst **a, t_lst **b);

/*
** rotate list up
*/

void				ra(t_lst **a, t_lst **b);
void				rb(t_lst **a, t_lst **b);
void				rr(t_lst **a, t_lst **b);

/*
** rotate list down
*/

void				rra(t_lst **a, t_lst **b);
void				rrb(t_lst **a, t_lst **b);
void				rrr(t_lst **a, t_lst **b);

/*
** move value from one list to another
*/

void				pa(t_lst **a, t_lst **b);
void				pb(t_lst **a, t_lst **b);

#endif
