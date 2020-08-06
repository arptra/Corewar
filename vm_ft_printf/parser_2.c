/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 18:09:59 by gemerald          #+#    #+#             */
/*   Updated: 2020/01/18 18:15:43 by bgerda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			find_type(va_list *factor, char sp, int flags[])
{
	if (sp == 'd' || sp == 'i' || sp == 'o' || sp == 'u' ||
			sp == 'x' || sp == 'X' || sp == 'p')
		return (print_int(factor, sp, flags));
	else if (sp == 'f' || sp == 'F'
			|| sp == 'e' || sp == 'E'
			|| sp == 'g' || sp == 'G')
		return (print_float(factor, sp, flags));
	else if (sp == 's' || sp == 'r')
		return (print_str(factor, sp, flags));
	else if (sp == 'c')
		return (print_char(factor, sp, flags));
	else
		return (print_trash(sp, flags));
}

int			voyager_size(char *str, int flags[])
{
	int	i;

	i = 0;
	if (str[i] != 'h' && str[i] != 'l' && str[i] != 'L')
		return (0);
	if (str[i] == 'h')
	{
		if (str[i + 1] == 'h')
			flags[8] = 44;
		else
			flags[8] = 4;
	}
	else if (str[i] == 'l')
	{
		if (str[i + 1] == 'l')
			flags[8] = 11;
		else
			flags[8] = 1;
	}
	else if (str[i] == 'L')
		flags[8] = 111;
	return ((flags[8] == 44 || flags[8] == 11) ? 2 : 1);
}

void		move_wild(int flags[], int *to_wp)
{
	if (flags[6] < 0)
	{
		if (*to_wp < 0)
		{
			*to_wp = -(*to_wp);
			flags[0] = '-';
		}
		flags[5] = *to_wp;
	}
	else
	{
		if (*to_wp >= 0)
			flags[7] = *to_wp;
	}
}

int			voyager_wp(char *str, int flags[], va_list *factor)
{
	int i;
	int to_wp;

	i = 0;
	to_wp = 0;
	if (str[i] == '*')
	{
		to_wp = va_arg((*factor), int);
		i++;
	}
	if (str[i] >= '0' && str[i] <= '9')
		to_wp = 0;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		to_wp = to_wp * 10 + ((int)str[i] - '0');
		i++;
	}
	move_wild(flags, &to_wp);
	return (i);
}
