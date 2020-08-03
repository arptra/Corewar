/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_binary.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umoff <umoff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 13:44:31 by umoff             #+#    #+#             */
/*   Updated: 2020/07/02 13:26:04 by umoff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_float.h"

static void	fix_point_binary(char *res, uint64_t *num, size_t bit_size,
								size_t whr_space)
{
	uint64_t	temp;
	char		bit;
	size_t		space;
	ssize_t		size;

	space = 0;
	size = bit_size;
	while (--size >= 0)
	{
		temp = *num >> size & 1;
		bit = temp + '0';
		ft_strncat(res + space, &bit, 1);
		++space;
		if (!(space % whr_space) && space != bit_size)
			ft_strncat(res + space, " ", 1);
	}
}

static void	double_binary(char *res, uint64_t *num)
{
	_Bool		sign;
	int32_t		exp2;
	uint64_t	mant;

	sign = get_sign(num);
	exp2 = get_exp(num);
	mant = get_mantissa(num);
	sign ? ft_strncpy(res, "1 ", 2) :
		ft_strncpy(res, "0 ", 2);
	fix_point_binary(res + 2, (uint64_t *)&exp2, 11, 11);
	ft_strncat(res + 2 + 11, " ", 1);
	fix_point_binary(res + 2 + 12, (uint64_t *)&mant, 52, 52);
}

static void	ldouble_binary(char *res, uint64_t *num)
{
	_Bool		sign;
	int32_t		exp2;
	uint64_t	mant;

	sign = get_lsign(num);
	exp2 = get_lexp(num);
	mant = get_lmantissa(num);
	sign ? ft_strncpy(res, "1 ", 2) :
			ft_strncpy(res, "0 ", 2);
	fix_point_binary(res + 2, (uint64_t *)&exp2, 15, 15);
	ft_strncat(res + 2 + 15, " ", 1);
	fix_point_binary(res + 2 + 16, (uint64_t *)&mant, 64, 64);
}

char		*get_binary(uint64_t *num, size_t bit_size, t_mkfld *fld,
						const char type)
{
	char		*res;

	if (!(res = ft_strnew(fld->lennum)))
		return (NULL);
	if (type == 'i')
		fix_point_binary(res, num, bit_size, 8);
	else if (type == 'f')
		double_binary(res, num);
	else if (type == 'd')
		ldouble_binary(res, num);
	return (res);
}

void		get_binaryd_by_type(t_prsng *tools, t_mkfld *fld)
{
	char *a;

	if (tools->type == 'c')
		a = get_binary((uint64_t *)&fld->nmbr.c, sizeof(char) * 8, fld, 'i');
	else if (tools->mdfirs == 0)
		a = get_binary((uint64_t *)&fld->nmbr.i, sizeof(int) * 8, fld, 'i');
	else if (tools->mdfirs & M_LL)
		a = get_binary((uint64_t *)&fld->nmbr.ll, sizeof(long long) * 8,
				fld, 'i');
	else if (tools->mdfirs & M_L)
		a = get_binary((uint64_t *)&fld->nmbr.l, sizeof(long) * 8, fld, 'i');
	else if (tools->mdfirs & M_H)
		a = get_binary((uint64_t *)&fld->nmbr.sh, sizeof(short) * 8, fld, 'i');
	else if (tools->mdfirs & M_HH)
		a = get_binary((uint64_t *)&fld->nmbr.c, sizeof(char) * 8, fld, 'i');
	ft_strncpy(&fld->str[fld->len], a, fld->lennum);
}
