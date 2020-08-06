/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 19:11:22 by gemerald          #+#    #+#             */
/*   Updated: 2019/09/12 23:50:16 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		nbr_len(int n)
{
	int len;
	int mark;

	len = 0;
	mark = 0;
	if (n == -2147483648)
		return (12);
	else if (n < 0)
	{
		mark = 1;
		n = -n;
	}
	else if (n == 0)
		len++;
	while (n != 0)
	{
		n = n / 10;
		len++;
	}
	return (len + mark + 1);
}

static int		ft_pow(int len)
{
	int c;

	c = 1;
	while (len > 0)
	{
		c = c * 10;
		len--;
	}
	return (c);
}

static void		ft_upload(char *toa, int n, int len)
{
	int i;

	i = 0;
	while (--len > 0)
	{
		toa[i] = n / ft_pow(len) + '0';
		n = n - (n / ft_pow(len)) * ft_pow(len);
		i++;
	}
	toa[i++] = n + '0';
	toa[i] = '\0';
}

char			*ft_itoa(int n)
{
	int		i;
	int		len;
	char	*toa;

	i = 0;
	len = nbr_len(n);
	if (!(toa = (char *)malloc(sizeof(char) * (len))))
		return (NULL);
	if (n == -2147483648)
	{
		toa[i++] = '-';
		toa[i++] = '2';
		n = 147483648;
		len = len - 3;
	}
	else if (n < 0)
	{
		toa[i++] = '-';
		n = -n;
		len = len - 2;
	}
	else if (n >= 0)
		len = len - 1;
	ft_upload(&toa[i], n, len);
	return (toa);
}
