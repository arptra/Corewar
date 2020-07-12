/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_float.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umoff <umoff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 14:14:27 by umoff             #+#    #+#             */
/*   Updated: 2020/07/02 13:31:48 by umoff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "high_precision.h"
#include "ft_ptintf.h"

static char	*initialize_dbl(t_result *res, t_dbl_comp *dblcomp, double number,
		t_prsng *tools)
{
	uint64_t	*dbl;

	dbl = (uint64_t *)&number;
	dblcomp->sign = get_sign(dbl);
	if ((dblcomp->exp_val = get_exp(dbl)) == 0x7FF)
	{
		if (!get_mantissa(dbl))
			return (print_inf(res, dblcomp->sign, tools->type));
		return (print_nan(res, tools->type));
	}
	if (!dblcomp->exp_val)
	{
		if (!get_mantissa(dbl))
			return (print_zero(res, dblcomp->sign, tools));
		dblcomp->exp_val = 1 - OFFSET_DBL;
		dblcomp->mant_val = get_mantissa(dbl);
	}
	else
	{
		dblcomp->exp_val -= OFFSET_DBL;
		dblcomp->mant_val = (1LL << 52) | get_mantissa(dbl);
	}
	dblcomp->mant_high_bits = dblcomp->mant_val >> 32;
	dblcomp->mant_low_bits = dblcomp->mant_val & 0xFFFFFFFF;
	return (NULL);
}

static void	process(t_result *res, t_high *hp, const t_dbl_comp *dblcomp,
		t_prsng *tools)
{
	insert_low_bits(hp, dblcomp->mant_high_bits, dblcomp->exp_val + 12, 1);
	insert_low_bits(hp, dblcomp->mant_low_bits, dblcomp->exp_val - 32 + 12, 1);
	fill_result(hp, 1, tools, res);
	if (*res->result)
		add_point(res, tools);
	insert_top_bits(hp, dblcomp->mant_high_bits, 52 - dblcomp->exp_val - 32, 0);
	insert_top_bits(hp, dblcomp->mant_low_bits, 52 - dblcomp->exp_val, 0);
	res->bf_len = 0;
	fill_result(hp, 0, tools, res);
	if (tools->type == 'e' || tools->type == 'E')
		fill_exp_chars(res, tools->type);
}

char		*print_double(t_prsng *tools, t_mkfld *fld, double number)
{
	t_dbl_comp	dblcomp;
	t_high		*hp;
	t_result	res;
	int			precision;

	res.len = -1;
	if ((res.result = initialize_dbl(&res, &dblcomp, number, tools)))
		return (res.result);
	if (!res.len)
		return (NULL);
	res.lg_10 = ft_floor(ft_log10(number));
	if (ft_tolower(tools->type) == 'g' || ft_tolower(tools->type) == 'a')
		return (calculate_g_a_result(tools, fld, res.lg_10));
	if (!(hp = hp_initializ()))
		return (NULL);
	res = create_str(res.lg_10, tools, fld);
	precision = tools->prec;
	if (!res.result)
		return (NULL);
	process(&res, hp, &dblcomp, tools);
	check_result(&res, tools, precision, fld);
	if (!res.len)
		return (NULL);
	free_hp(hp);
	return (res.result);
}
