/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_itoa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 22:42:16 by gemerald          #+#    #+#             */
/*   Updated: 2020/01/18 20:20:33 by bgerda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int							nbr_len(unsigned long long int nbr,
															int base)
{
	int	len;
	int	mark;

	len = 0;
	mark = 0;
	if (nbr == 0)
		len++;
	while (nbr != 0)
	{
		nbr = nbr / base;
		len++;
	}
	return (len + mark);
}

static unsigned long long	ft_pow(int len, int base)
{
	unsigned long long	c;

	c = 1;
	while (len > 0)
	{
		c = c * base;
		len--;
	}
	return (c);
}

static void					ft_upload(t_upload param)
{
	int		i;
	char	*digit;

	digit = "0123456789abcdef";
	i = 0;
	while (--param.len > 0)
	{
		if (param.sp == 'X')
			uputchar_fd(ft_toupper(digit[param.nbr /
			ft_pow(param.len, param.base)]), param.fd, 0);
		else
			uputchar_fd(digit[param.nbr /
							ft_pow(param.len, param.base)], param.fd, 0);
		param.nbr = param.nbr - (param.nbr /
				ft_pow(param.len, param.base))
						* ft_pow(param.len, param.base);
		i++;
	}
	if (param.sp == 'X')
		uputchar_fd(ft_toupper(digit[param.nbr]), param.fd, 0);
	else
		uputchar_fd(digit[param.nbr], param.fd, 0);
}

int							print_itoa(unsigned long long n,\
							int base, char sp, int fd)
{
	int						len;
	unsigned long long		nbr;
	t_upload				param;

	nbr = n;
	len = nbr_len(nbr, base);
	param.base = base;
	param.fd = fd;
	param.len = len;
	param.nbr = nbr;
	param.sp = sp;
	ft_upload(param);
	return (len);
}
