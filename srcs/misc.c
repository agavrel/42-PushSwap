/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 22:14:28 by angavrel          #+#    #+#             */
/*   Updated: 2018/02/11 22:22:18 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

inline void	error_handler(size_t i)
{
	static const char	*error_message[4] = \
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

void		check_duplicate(size_t n, int lst[n])
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
