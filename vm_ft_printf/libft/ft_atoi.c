/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 18:39:45 by gemerald          #+#    #+#             */
/*   Updated: 2019/11/11 21:45:17 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
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
	while ((str[i] >= '0') && (str[i] <= '9'))
	{
		if ((result * 10) < result)
			return ((mark == -1) ? 0 : -1);
		result = (result * 10) + (str[i] - '0');
		i++;
	}
	return (result * mark);
}
