/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 22:12:42 by angavrel          #+#    #+#             */
/*   Updated: 2018/02/11 22:23:00 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

int				is_sorted_lst(t_lst *lst)
{
	t_lst	*begin;

	begin = lst->prev;
	while (lst != begin)
	{
		if (lst->value > lst->next->value)
			return (0);
		lst = lst->next;
	}
	return (1);
}

static inline	t_lst	*lst_create()
{
	t_lst	*lst;

	if (!(lst = malloc(sizeof(t_lst))))
		error_handler(1);
	lst->value = 0;
	lst->next = NULL;
	lst->prev = NULL;
	return (lst);
}

t_lst			*lst_new(size_t n)
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
