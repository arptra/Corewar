/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 22:15:49 by gemerald          #+#    #+#             */
/*   Updated: 2020/01/18 17:57:23 by bgerda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void					only_wide_di(long long int *nbr, int flags[], int *i)
{
	int wide;

	wide = flags[5] - flags[10];
	if (flags[4] >= 0 && flags[0] < 0)
	{
		flags_di(nbr, flags, i);
		to_side_di(wide, '0', i, flags[12]);
		if (!(*nbr) && flags[6] >= 0 && flags[7] < 1)
			;
		else
			(*i) += print_itoa((*nbr), 10, 'x', flags[12]);
	}
	else if (flags[0] < 0)
	{
		to_side_di(wide, ' ', i, flags[12]);
		flags_di(nbr, flags, i);
		if (!(*nbr) && flags[6] >= 0 && flags[7] < 1)
			;
		else
			(*i) += print_itoa((*nbr), 10, 'x', flags[12]);
	}
	else
		only_wide_di_next(nbr, flags, i, wide);
}

void					only_precision_di(long long int *nbr,\
											int flags[], int *i)
{
	int len;

	len = nbr_len((*nbr), 10);
	if (flags[7] < len)
	{
		flags_di(nbr, flags, i);
		if (!(*nbr) && flags[6] >= 0 && flags[7] < 1)
			;
		else
			(*i) += print_itoa((*nbr), 10, 'x', flags[12]);
	}
	else
	{
		flags_di(nbr, flags, i);
		to_side_di(flags[7] - len, '0', i, flags[12]);
		if (!(*nbr) && flags[6] >= 0 && flags[7] < 1)
			;
		else
			(*i) += print_itoa((*nbr), 10, 'x', flags[12]);
	}
}

void					precision_di(long long int *nbr, int flags[], int *i)
{
	int len;

	len = flags[5] - flags[10];
	if (flags[5] < 0 || flags[5] < flags[7])
		only_precision_di(nbr, flags, i);
	else
	{
		if (flags[0] < 0)
		{
			to_side_di(len, ' ', i, flags[12]);
			only_precision_di(nbr, flags, i);
		}
		else
		{
			only_precision_di(nbr, flags, i);
			to_side_di(len, ' ', i, flags[12]);
		}
	}
}

int						print_di(va_list *factor, int flags[])
{
	int				i;
	long long int	nbr;

	i = 0;
	nbr = signed_arg(factor, flags);
	flags[10] = nbr_len(((nbr > 0) ? nbr : -nbr), 10);
	if (flags[7] > flags[10])
		flags[10] = flags[7];
	kill_wide_di(&nbr, flags);
	if (flags[5] < 0 && flags[7] < 0)
	{
		flags_di(&nbr, flags, &i);
		if (!nbr && flags[6] >= 0 && flags[7] < 1)
			;
		else
			i += print_itoa(nbr, 10, 'x', flags[12]);
	}
	if (flags[5] >= 0 && flags[7] < 0)
		only_wide_di(&nbr, flags, &i);
	if (flags[7] >= 0)
		precision_di(&nbr, flags, &i);
	return (i);
}

int						print_int(va_list *factor, char sp, int flags[])
{
	if (sp == 'd' || sp == 'i')
		return (print_di(factor, flags));
	if (sp == 'u' || sp == 'x' || sp == 'X' || sp == 'p')
		return (print_u(factor, flags, sp));
	if (sp == 'o')
		return (print_o(factor, flags, sp));
	return (0);
}
