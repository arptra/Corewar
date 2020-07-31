/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_uint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 15:51:21 by gemerald          #+#    #+#             */
/*   Updated: 2020/01/18 17:46:28 by bgerda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	only_precision_u(unsigned long long int *nbr,\
							int flags[], int *i, int base)
{
	int len;

	len = nbr_len((*nbr), base);
	if (flags[7] < len)
	{
		flags_u(nbr, flags, i);
		if ((!(*nbr) && flags[6] >= 0) ||
				((flags[9] == 'x' || flags[9] == 'X' || flags[9] == 'p') &&
				(!(*nbr) && flags[6] >= 0 && flags[7] <= 0 && flags[3] >= 0)))
			;
		else
			(*i) += print_itoa((*nbr), base, (char)flags[9], flags[12]);
	}
	else
	{
		flags_u(nbr, flags, i);
		to_side_u(flags[7] - len, '0', i, flags[12]);
		if (!(*nbr) && flags[6] >= 0 && flags[7] < 1)
			;
		else
			(*i) += print_itoa((*nbr), base, (char)flags[9], flags[12]);
	}
}

void	precision_u(unsigned long long int *nbr, int flags[], int *i, int base)
{
	int len;

	len = flags[10];
	if (flags[7] >= len)
		len = flags[5] - flags[7];
	else
		len = flags[5] - len;
	if (flags[5] < 0 || flags[5] < flags[7])
		only_precision_u(nbr, flags, i, base);
	else
	{
		if (flags[0] < 0)
		{
			to_side_u(len, ' ', i, flags[12]);
			only_precision_u(nbr, flags, i, base);
		}
		else
		{
			only_precision_u(nbr, flags, i, base);
			to_side_u(len, ' ', i, flags[12]);
		}
	}
}

void	print_u_next(unsigned long long int *nbr, int flags[], int *i, int base)
{
	flags_u(nbr, flags, i);
	if (!nbr && flags[6] >= 0 && flags[7] < 1 && flags[3] < 0)
		;
	else
		i += print_itoa((*nbr), base, (char)flags[9], flags[12]);
}

int		print_u(va_list *factor, int flags[], char sp)
{
	int						i;
	int						base;
	unsigned long long int	nbr;

	i = 0;
	flags[9] = (int)sp;
	base = 10;
	if (sp == 'X' || sp == 'x' || sp == 'p')
		base = 16;
	else if (sp == 'o')
		base = 8;
	nbr = unsigned_arg(factor, flags);
	flags[10] = nbr_len(nbr, base);
	if (!nbr && sp == 'o' && flags[3] >= 0 && (flags[6] && flags[7] < 1))
		flags[10]--;
	if (flags[7] > flags[10])
		flags[10] = flags[7];
	kill_wide(&nbr, flags);
	if (flags[5] < 0 && flags[7] < 0)
		print_u_next(&nbr, flags, &i, base);
	if (flags[5] >= 0 && flags[7] < 0)
		only_wide_u(&nbr, flags, &i, base);
	if (flags[7] >= 0)
		precision_u(&nbr, flags, &i, base);
	return (i);
}
