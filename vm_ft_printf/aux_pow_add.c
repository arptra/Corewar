/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_pow_add.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgerda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 15:32:24 by bgerda            #+#    #+#             */
/*   Updated: 2020/01/18 21:32:36 by bgerda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		aux_wpart1(t_double **var, t_num **num, char *carry, int tmp)
{
	char	res[BUFF];

	if (tmp == 0)
	{
		if (((*num)->num1[ft_strlen((*num)->num1) -
					(1 + (*num)->precision)] - '0') >= 5)
			carry = rounding((*num)->num1, (*num)->num2,
									res, (*num)->precision);
		ft_strclr(res);
		ft_add((*num)->num3, carry, res);
		ft_strncpy((*num)->num3, res, ft_strlen((*num)->num1) + 1);
		(*var)->w_flag = 0;
	}
	else
	{
		if (((*num)->num1[tmp - 1] - '0') >= 5)
			carry = rounding((*num)->num1, (*num)->num2,
											res, (*num)->precision);
		ft_strclr(res);
		ft_add((*num)->num3, carry, res);
		ft_strncpy((*num)->num3, res, ft_strlen((*num)->num1) + 1);
	}
	return ((*num)->precision + 1);
}

int		preoutput2(t_double *var, t_num *num)
{
	int		tmp;
	int		j;
	char	*carry;

	j = 0;
	carry = "0";
	tmp = 0;
	if (num->precision == 1 || num->precision == 0)
		j = j + aux_wpart1(&var, &num, carry, tmp);
	else if ((tmp = (int)ft_strlen(num->num1) - num->precision) > 0)
	{
		j = j + aux_wpart1(&var, &num, carry, tmp);
		var->w_flag = 1;
		num->len = tmp;
	}
	else if ((tmp = (int)ft_strlen(num->num1) - num->precision) <= 0)
	{
		var->w_flag = -1;
		num->len = tmp;
		j = num->precision + 1;
	}
	return (j);
}

void	add_aux(char *num1, char *num2, int counter, char *dig)
{
	char	tmp[BUFF];

	ft_strclr(tmp);
	if (counter < 0)
	{
		get_mod(counter, num2, dig);
		fill_zeros(num1, num2, tmp);
		ft_add(num1, num2, tmp);
		ft_strncpy(num1, tmp, ft_strlen(tmp) + 1);
	}
	else if (counter >= 0)
	{
		get_mod(counter, num1, dig);
		ft_add(num1, num2, tmp);
		ft_strncpy(num2, tmp, ft_strlen(tmp) + 1);
	}
}

void	mod_aux(int counter, char *num1, char *dig, int *flag)
{
	get_mod(counter, num1, dig);
	*flag = counter;
}

int		preoutput(t_double *var, t_num *num)
{
	int	j;

	j = 0;
	if (var->e - var->shift < 0 || (var->e - var->shift == 0
				&& var->shift == 16382))
	{
		var->f_flag = 0;
		var->power = -(var->e - var->shift - var->lshift);
		add_aux(num->num1, num->num2, -var->power, "5");
		j = j + 1;
	}
	else
	{
		var->f_flag = -1;
		var->power = var->pow;
		add_aux(num->num4, num->num3, var->power, "2");
		j = j + (int)ft_strlen(num->num3);
	}
	if (num->num1[0] == 0 && num->num2[0] == 0)
		num->num1[0] = '0';
	return (j);
}
