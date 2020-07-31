/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_eg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgerda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 14:06:23 by bgerda            #+#    #+#             */
/*   Updated: 2020/01/18 20:13:41 by bgerda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_eg(t_double var, t_num num, int len, char sign)
{
	output(var, num);
	uputchar_fd(var.sp, var.fd, 0);
	uputchar_fd(sign, var.fd, 0);
	if (len / 10 == 0)
		uputchar_fd('0', var.fd, 0);
	ft_putnbr(len);
}

void	pos_pow(t_num *num)
{
	ft_strncat(num->num1, num->num3, ft_strlen(num->num3) - 1);
	num->num3[0] = num->num3[ft_strlen(num->num3) - 1];
	num->num3[1] = '\0';
}

void	neg_pow(t_num *num, int len)
{
	num->num3[0] = num->num1[len];
	num->num3[1] = '\0';
	num->num1[len] = '\0';
}

int		print_g_pos(t_double var, t_num num)
{
	int len2;
	int j;

	if ((len2 = ft_strlen(num.num3)) <= num.precision)
	{
		if (num.precision > (int)ft_strlen(num.num1))
			num.precision = (int)ft_strlen(num.num1) - 1;
		else if ((int)ft_strlen(num.num1) >= num.precision)
			num.precision = num.precision - len2;
		j = preoutput2(&var, &num);
		output(var, num);
	}
	else
	{
		if (num.precision != 0)
			num.precision--;
		pos_pow(&num);
		j = preoutput2(&var, &num);
		var.sp = var.sp - 2;
		print_eg(var, num, len2 - 1, '+');
	}
	return (j);
}

int		print_g_neg(t_double var, t_num num, int len1, int len2)
{
	int j;

	j = 0;
	if (len1 > 3)
	{
		if (num.precision > len2 - len1)
			num.precision = len2 - len1;
		neg_pow(&num, len2 - len1);
		var.f_flag = -1;
		j = j + preoutput2(&var, &num);
		var.sp = var.sp - 2;
		print_eg(var, num, len1 + 1, '-');
	}
	else
	{
		if (num.precision > len2 - len1)
			num.precision = len2 - len1;
		else
			num.precision++;
		j = j + preoutput2(&var, &num);
		output(var, num);
	}
	return (j);
}
