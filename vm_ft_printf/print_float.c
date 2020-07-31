/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_float.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 10:09:22 by gemerald          #+#    #+#             */
/*   Updated: 2020/01/18 19:40:24 by bgerda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void						print_f(t_double var, int flags[], int *i)
{
	*i = *i + print_double(var, flags);
}

void						to_side_f(int wide, char field, int *i, int fd)
{
	while (wide-- && wide >= 0)
	{
		uputchar_fd(field, fd, 0);
		(*i)++;
	}
}

void						only_wide_f(t_double var, int flags[], int *i)
{
	if (flags[5] > 0 && flags[0] > 0)
	{
		flags_f(flags, i);
		print_f(var, flags, i);
		to_side_f(flags[5], (char)(' '), i, flags[12]);
	}
	else
	{
		flags_f(flags, i);
		print_f(var, flags, i);
	}
}

int							print_float(va_list *factor, char sp, int flags[])
{
	int				i;
	long double		nbr;
	t_double		var;

	i = 0;
	nbr = signed_float(factor, flags);
	init_nbr(&var, nbr, flags, sp);
	kill_wide_f(&nbr, flags);
	if (flags[5] > 0 && flags[0] < 0 && flags[4] < 0)
	{
		to_side_f(flags[5], ' ', &i, flags[12]);
		flags_f(flags, &i);
		print_f(var, flags, &i);
	}
	else if (flags[5] > 0 && flags[0] < 0 && flags[4] > 0)
	{
		flags_f(flags, &i);
		to_side_f(flags[5], '0', &i, flags[12]);
		print_f(var, flags, &i);
	}
	else
		only_wide_f(var, flags, &i);
	return (i);
}
