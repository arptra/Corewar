/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_trash.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 22:10:48 by gemerald          #+#    #+#             */
/*   Updated: 2020/01/18 17:50:54 by bgerda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		trash_pc(char sp, int *i, int fd)
{
	uputchar_fd(sp, fd, 0);
	(*i)++;
}

int				print_trash(char sp, int flags[])
{
	int i;

	i = 0;
	if (flags[5] >= 0 && flags[0] >= 0)
	{
		uputchar_fd(sp, flags[12], 0);
		i++;
		to_side_di(flags[5] - 1, ' ', &i, flags[12]);
	}
	else if (flags[5] >= 0 && flags[0] < 0 && flags[4] >= 0)
	{
		to_side_di(flags[5] - 1, '0', &i, flags[12]);
		uputchar_fd(sp, flags[12], 0);
		i++;
	}
	else if (flags[5] >= 0)
	{
		to_side_di(flags[5] - 1, ' ', &i, flags[12]);
		uputchar_fd(sp, flags[12], 0);
		i++;
	}
	else
		trash_pc(sp, &i, flags[12]);
	return (i);
}
