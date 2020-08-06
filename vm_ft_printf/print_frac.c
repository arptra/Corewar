/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_frac.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgerda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 14:21:32 by bgerda            #+#    #+#             */
/*   Updated: 2020/01/18 14:24:58 by bgerda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_wpart(char *str, int fd)
{
	if (*(++str))
		print_wpart(str, fd);
	uputchar_fd(*(--str), fd, 0);
}

void	print_fpart(char *str, int i, int prec, int fd)
{
	if (*(++str))
		print_fpart(str, ++i, prec, fd);
	if (i > prec)
		uputchar_fd(*(--str), fd, 0);
}

char	*rounding(char *num1, char *num2, char *res, int prec)
{
	int tmp;

	tmp = prec;
	ft_strclr(num2);
	ft_strclr(res);
	while (--prec >= 0)
		num2[prec] = '0';
	num2[0] = '1';
	fill_zeros(num1, num2, res);
	ft_add(num1, num2, res);
	if (ft_strlen(res) > ft_strlen(num1) || tmp == 0)
	{
		ft_strncpy(num1, res, ft_strlen(num1));
		return ("1");
	}
	else
		ft_strncpy(num1, res, ft_strlen(res) + 1);
	return ("0");
}

void	sel_wpart(t_double var, t_num num)
{
	if (var.f_flag == 0)
	{
		uputchar_fd('0', var.fd, 0);
		if (num.precision != 0 || num.grate == '#')
			uputchar_fd('.', var.fd, 0);
	}
	else if (var.f_flag == -1)
	{
		print_wpart(num.num3, var.fd);
		if (num.precision != 0 || num.grate == '#')
			uputchar_fd('.', var.fd, 0);
	}
}

void	output(t_double var, t_num num)
{
	int i;

	i = 0;
	if (var.w_flag == 0)
	{
		sel_wpart(var, num);
		if (num.precision != 0)
			uputchar_fd(num.num1[ft_strlen(num.num1) - 1], var.fd, 0);
	}
	else if (var.w_flag == 1)
	{
		sel_wpart(var, num);
		print_fpart(num.num1, i, num.len, var.fd);
	}
	else if (var.w_flag == -1)
	{
		sel_wpart(var, num);
		if (num.num1[0] != '\0')
			print_fpart(num.num1, i, num.len, var.fd);
		while (num.len++ < 0)
			uputchar_fd('0', var.fd, 0);
	}
}
