/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_floor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umoff <umoff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 14:14:05 by umoff             #+#    #+#             */
/*   Updated: 2020/07/02 13:39:24 by umoff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "libft.h"

double		ft_floor(double num)
{
	uint64_t		intg;
	uint64_t		int_res;
	struct s_comp	comp;
	int32_t			shifted_exp;
	double			res;

	ft_memcpy(&intg, &num, sizeof(double));
	if ((comp.exp_val = (intg >> 52 & 0x7FF) - 1023) < 0)
		return (-(num < 0));
	if ((shifted_exp = 52 - comp.exp_val) <= 0)
		return (num);
	comp.mant = (intg & ((1LL << 52) - 1)) | (1LL << 52);
	res = (double)(comp.mant >> shifted_exp);
	if (num < 0)
		res *= -1;
	ft_memcpy(&int_res, &res, sizeof(double));
	if (res < 0 && int_res != intg)
		return (--res);
	return (res);
}

long double	ft_floorl(long double num)
{
	uint64_t		*intg;
	uint64_t		*int_res;
	struct s_comp	comp;
	int32_t			shifted_exp;
	long double		res;

	intg = (uint64_t *)&num;
	if ((comp.exp_val = (*(intg + 1) & 0x7FFF) - 16383) < 0)
		return (-(num < 0));
	if ((shifted_exp = 63 - comp.exp_val) <= 0)
		return (num);
	comp.mant = *intg & 0xFFFFFFFFFFFFFFFF;
	res = (long double)(comp.mant >> shifted_exp);
	if (num < 0)
		res *= -1;
	int_res = (uint64_t *)&res;
	if (res < 0 && (*int_res != *intg || *(int_res + 1) != *(intg + 1)))
		return (--res);
	return (res);
}
