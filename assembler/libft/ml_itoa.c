/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umoff <umoff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 14:13:42 by umoff             #+#    #+#             */
/*   Updated: 2020/07/02 13:49:16 by umoff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	len_num(int num)
{
	if (num >= 0 && num <= 9)
		return (1);
	return (len_num(num / 10) + 1);
}

char			*ml_itoa(int n, u_int32_t lst_num)
{
	char			*str;
	size_t			len;
	unsigned int	nbr;

	len = len_num(n);
	if (!(str = ml_strnew(len, lst_num)))
		return (NULL);
	nbr = (n < 0) ? (unsigned int)(-n) : (unsigned int)(n);
	if (nbr == 0)
		*str = '0';
	while (len-- && nbr)
	{
		str[len] = (nbr % 10) + '0';
		nbr /= 10;
	}
	if (n < 0)
		str[len] = '-';
	return (str);
}
