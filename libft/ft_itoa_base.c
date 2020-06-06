/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: u18188899 <u18188899@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/31 12:47:59 by u18188899         #+#    #+#             */
/*   Updated: 2020/05/31 12:54:32 by u18188899        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ft_abs(int n)
{
	unsigned int	t1;

	if (n < 0)
	{
		t1 = -n;
	}
	else
	{
		t1 = n;
	}
	return (t1);
}

static unsigned int	ft_get_depth(int n, int base)
{
	unsigned int	i1;
	unsigned int	t1;

	if (n < 0)
		i1 = 2;
	else
		i1 = 1;
	t1 = ft_abs(n);
	while (t1 >= (unsigned int)base)
	{
		t1 = t1 / base;
		i1++;
	}
	return (i1);
}

char				*ft_itoa_base(int n, int base)
{
	char			*fresh;
	unsigned int	i1;
	unsigned int	t1;

	if (n < 0 && base != 10)
		return (NULL);
	fresh = (char*)malloc(sizeof(char) * (ft_get_depth(n,base) + 1));
	if (!fresh)
		return (NULL);
	t1 = ft_abs(n);
	i1 = ft_get_depth(n,base);
	fresh[i1] = '\0';
	while (t1 >= (unsigned int)base)
	{
		fresh[--i1] = t1 % base + '0';
		t1 = t1 / base;
	}
	fresh[--i1] = t1 + '0';
	if (n < 0)
		fresh[--i1] = '-';
	return (fresh);
}
