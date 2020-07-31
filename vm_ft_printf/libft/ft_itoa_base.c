/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa_base.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 21:54:55 by gemerald          #+#    #+#             */
/*   Updated: 2019/11/11 21:44:17 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		nbr_len(long nbr, int base)
{
	int len;
	int mark;

	len = 0;
	mark = 0;
	if (nbr < 0)
	{
		mark = 1;
		nbr = -nbr;
	}
	else if (nbr == 0)
		len++;
	while (nbr != 0)
	{
		nbr = nbr / base;
		len++;
	}
	return (len + mark + 1);
}

static int		ft_pow(int len, int base)
{
	int c;

	c = 1;
	while (len > 0)
	{
		c = c * base;
		len--;
	}
	return (c);
}

static void		ft_upload(char *toa, long nbr, int len, int base)
{
	int		i;
	char	*digit;

	digit = "0123456789abcdef";
	i = 0;
	while (--len > 0)
	{
		toa[i] = digit[nbr / ft_pow(len, base)];
		nbr = nbr - (nbr / ft_pow(len, base)) * ft_pow(len, base);
		i++;
	}
	toa[i++] = digit[nbr];
	toa[i] = '\0';
}

char			*ft_itoa_base(int n, int base)
{
	int		i;
	int		len;
	char	*toa;
	long	nbr;

	nbr = n;
	i = 0;
	len = nbr_len(nbr, base);
	if (!(toa = (char *)malloc(sizeof(char) * (len))))
		return (NULL);
	if (nbr < 0)
	{
		toa[i++] = '-';
		nbr = -nbr;
		len = len - 2;
	}
	else if (nbr >= 0)
		len = len - 1;
	ft_upload(&toa[i], nbr, len, base);
	return (toa);
}
