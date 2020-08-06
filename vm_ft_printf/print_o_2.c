/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_o_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 18:11:01 by gemerald          #+#    #+#             */
/*   Updated: 2020/01/18 17:51:25 by bgerda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	flags_o(unsigned long long int *nbr, int flags[], int *i)
{
	if ((char)flags[9] == 'o' && (*nbr) && flags[3] >= 0)
	{
		if (flags[4] >= 0)
			flags[5]--;
		uputchar_fd('0', flags[12], 0);
		(*i)++;
	}
}

void	kill_wide_o(unsigned long long int *nbr, int flags[])
{
	if (!(*nbr) && flags[7] == 0 && flags[9] == 'o' && flags[3] < 0)
		flags[5]++;
	else if (flags[3] >= 0 && (char)flags[9] == 'o' &&
			(*nbr) && flags[6] >= 0 && flags[7] >= 0)
	{
		flags[10]--;
		flags[7]--;
		flags[5]--;
	}
	if (*nbr && flags[3] >= 0 && flags[4] < 0 && flags[5] > 0 &&
			flags[6] < 0 && flags[7] < 0)
		flags[5]--;
}

void	to_side_o(int wide, char field, int *i, int fd)
{
	while (wide-- && wide >= 0)
	{
		uputchar_fd(field, fd, 0);
		(*i)++;
	}
}
