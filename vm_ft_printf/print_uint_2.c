/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_uint_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 18:11:14 by gemerald          #+#    #+#             */
/*   Updated: 2020/01/18 17:47:03 by bgerda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	flags_u(unsigned long long int *nbr, int flags[], int *i)
{
	if ((flags[3] >= 0 && ((char)flags[9] == 'x' ||
					(char)flags[9] == 'X') && *nbr > 0) ||
			((char)flags[9] == 'p' && !(*nbr)))
	{
		if ((char)flags[9] == 'x' || (char)flags[9] == 'p')
			ft_putstr_fd("0x", flags[12]);
		else
			ft_putstr_fd("0X", flags[12]);
		(*i) += 2;
	}
	else if (flags[3] >= 0 && (char)flags[9] == 'o')
	{
		uputchar_fd('0', flags[12], 0);
		(*i)++;
	}
	else if ((char)flags[9] == 'p')
	{
		ft_putstr_fd("0x", flags[12]);
		(*i) += 2;
	}
}

void	kill_wide(unsigned long long int *nbr, int flags[])
{
	if (!(*nbr) && flags[7] == 0 && flags[9] != 'o')
		flags[5]++;
	if (!(*nbr) && flags[7] == 0 && flags[9] == 'o' && flags[3] < 0)
		flags[5]++;
	else if ((flags[3] >= 0 && *nbr && ((char)flags[9] == 'x' ||
			(char)flags[9] == 'X')) || ((char)flags[9] == 'p' && !(*nbr)))
		flags[10] += 2;
	else if (flags[3] >= 0 && (char)flags[9] == 'o')
	{
		flags[10] += 1;
		flags[7]--;
	}
	else if ((char)flags[9] == 'p')
		flags[10] += 2;
}

void	to_side_u(int wide, char field, int *i, int fd)
{
	while (wide-- && wide >= 0)
	{
		uputchar_fd(field, fd, 0);
		(*i)++;
	}
}

void	only_wide_u_next(unsigned long long int *nbr, int flags[],\
							int *i, int base)
{
	flags_u(nbr, flags, i);
	if ((!(*nbr) && flags[6] >= 0 && flags[7] < 1) ||
			(flags[3] > 0 && flags[9] == 'o' && !(*nbr)))
		;
	else
		(*i) += print_itoa((*nbr), base, (char)flags[9], flags[12]);
	to_side_u(flags[5] - flags[10], ' ', i, flags[12]);
}

void	only_wide_u(unsigned long long int *nbr, int flags[], int *i, int base)
{
	int wide;

	wide = flags[5] - flags[10];
	if (flags[4] >= 0 && flags[0] < 0)
	{
		flags_u(nbr, flags, i);
		to_side_u(wide, '0', i, flags[12]);
		if (!(*nbr) && flags[6] >= 0 && flags[7] < 1 && flags[3] < 0)
			;
		else
			(*i) += print_itoa((*nbr), base, (char)flags[9], flags[12]);
	}
	else if (flags[0] < 0)
	{
		to_side_u(wide, ' ', i, flags[12]);
		flags_u(nbr, flags, i);
		if ((!(*nbr) && flags[6] >= 0 && flags[7] < 1 && flags[3] < 0) ||
				(flags[3] > 0 && flags[9] == 'o' && !(*nbr)))
			;
		else
			(*i) += print_itoa((*nbr), base, (char)flags[9], flags[12]);
	}
	else
		only_wide_u_next(nbr, flags, i, base);
}
