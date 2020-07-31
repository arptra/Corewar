/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 21:47:47 by gemerald          #+#    #+#             */
/*   Updated: 2019/11/11 21:52:20 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		char_to_int(char c)
{
	char		*stop;
	int			i;

	i = 0;
	stop = "0123456789abcdef";
	c = ft_tolower(c);
	while (stop[i])
	{
		if (stop[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int				ft_atoi_base(const char *str, int base)
{
	int						i;
	int						mark;
	unsigned long long int	result;

	i = 0;
	result = 0;
	mark = 1;
	while ((str[i] == '\f' || str[i] == '\n' || str[i] == '\r' ||
				str[i] == '\v' || str[i] == '\t' || str[i] == ' '))
		i++;
	if ((str[i] == '-') || (str[i] == '+'))
	{
		if (str[i] == '-')
			mark = -1;
		i++;
	}
	while (((str[i] >= '0') && (str[i] <= '9')) || ((str[i] >= 'a')
			&& (str[i] <= 'f')) || ((str[i] >= 'A') && (str[i] <= 'F')))
	{
		if ((result * base) < result)
			return ((mark == -1) ? 0 : -1);
		result = (result * base) + char_to_int(str[i]);
		i++;
	}
	return (result * mark);
}
