/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   longdiv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgerda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 16:11:03 by bgerda            #+#    #+#             */
/*   Updated: 2020/01/18 16:14:02 by bgerda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		smul(const char *a, char *c, int sym, int size)
{
	int i;
	int temp;
	int carry;

	carry = 0;
	i = -1;
	while (++i < size)
	{
		temp = (a[i] - '0') * sym + carry;
		carry = temp / 10;
		c[i] = (temp - carry * 10) + '0';
	}
	if (carry)
		c[i++] = carry + '0';
	c[i] = '\0';
	i = -1;
	while (c[++i] != '\0')
		;
	return (i);
}

void	check_pow(int *size, int *sign, char *c, char *a)
{
	if (*size < 0)
	{
		*size = -(*size);
		*sign = 1;
	}
	if (*size == 1)
		ft_strncpy(c, &a[0], 3);
	if (*size == 0)
		ft_strncpy(c, "1", 3);
}

void	get_mod(int size, char *c, char *a)
{
	int i;
	int sign;
	int len;
	int sym;

	i = -1;
	len = 1;
	sign = 0;
	check_pow(&size, &sign, c, a);
	sym = a[0] - '0';
	while (++i < size - 1)
	{
		len = smul(a, c, sym, len);
		a = c;
	}
	len = ft_strlen(c);
	if (sign == 1)
	{
		while (len < size)
			c[len++] = '0';
	}
	c[len] = '\0';
}

void	add_case(int temp, char *c, int *carry, int i)
{
	if (temp >= 10)
	{
		c[i] = (temp - 10) + '0';
		*carry = 1;
	}
	else
	{
		c[i] = temp + '0';
		*carry = 0;
	}
}

void	ft_add(char *a, char *b, char *c)
{
	int	temp;
	int	carry;
	int	i;
	int	size;

	i = -1;
	carry = 0;
	size = ft_strlen(b);
	while (++i < size)
	{
		temp = (a[i] - '0') + (b[i] - '0') + carry;
		add_case(temp, c, &carry, i);
	}
	size = ft_strlen(a);
	while (i < size)
	{
		temp = (a[i] - '0') + carry;
		add_case(temp, c, &carry, i);
		i++;
	}
	if (carry)
		c[i++] = carry + '0';
	c[i] = '\0';
}
