/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_float_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgerda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 14:09:31 by bgerda            #+#    #+#             */
/*   Updated: 2020/01/18 20:10:07 by bgerda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	pow_add(t_double *var, t_num *num)
{
	while (var->m / 2 != 0)
	{
		if (var->m % 2 == 1 && var->counter >= var->e - var->shift)
		{
			var->power = var->counter - (var->e - var->shift) + 1;
			if (var->f_flag == 0)
				mod_aux(-var->power, num->num1, "5", &var->f_flag);
			else
				add_aux(num->num1, num->num2, -var->power, "5");
		}
		else if (var->m % 2 == 1 && var->counter != var->e - var->shift)
		{
			var->power = -(var->counter - (var->e - var->shift) + 1);
			if (var->w_flag == -1)
				mod_aux(var->power, num->num3, "2", &var->w_flag);
			else
				add_aux(num->num4, num->num3, var->power, "2");
		}
		var->m = var->m / 2;
		var->counter--;
	}
}

int		output_e(t_double var, t_num num)
{
	int len2;
	int j;
	int len1;

	if (var.pow >= 0)
	{
		len2 = ft_strlen(num.num3);
		pos_pow(&num);
		j = preoutput2(&var, &num);
		print_eg(var, num, len2 - 1, '+');
	}
	else
	{
		len1 = 0;
		len2 = (int)ft_strlen(num.num1) - 1;
		while (num.num1[len2 - len1] == '0')
			len1++;
		neg_pow(&num, len2 - len1);
		var.f_flag = -1;
		j = preoutput2(&var, &num);
		print_eg(var, num, len1 + 1, '-');
	}
	return (j);
}

int		output_g(t_double var, t_num num)
{
	int len1;
	int len2;
	int j;

	if (var.pow >= 0)
		j = print_g_pos(var, num);
	else
	{
		if (num.precision != 0)
			num.precision--;
		len1 = 0;
		len2 = (int)ft_strlen(num.num1) - 1;
		while (num.num1[len2 - len1] == '0')
			len1++;
		j = print_g_neg(var, num, len1, len2);
	}
	return (j);
}

void	init(t_double *var, t_num *num, int flags[])
{
	ft_strclr(num->num1);
	ft_strclr(num->num2);
	ft_strclr(num->num3);
	ft_strclr(num->num4);
	var->f_flag = 0;
	var->w_flag = -1;
	var->fd = flags[12];
	num->precision = flags[7];
	num->grate = flags[3];
}

int		print_double(t_double var, int flags[])
{
	int		j;
	t_num	num;

	init(&var, &num, flags);
	pow_add(&var, &num);
	j = preoutput(&var, &num);
	if (var.sp == 'f')
	{
		j = j + preoutput2(&var, &num);
		output(var, num);
	}
	if (var.sp == 'e' || var.sp == 'E')
		j = j + output_e(var, num);
	if (var.sp == 'g' || var.sp == 'G')
		j = j + output_g(var, num);
	return (j);
}
