/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_flag_intf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umoff <umoff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 14:15:44 by umoff             #+#    #+#             */
/*   Updated: 2020/07/02 13:29:45 by umoff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "high_precision.h"

void	check_e_intg_res(t_result *res)
{
	if (*res->buff == '0')
		clear_res_buff(res);
	else if (res->bf_len > 1)
	{
		ft_strncpy(res->result, res->buff, 1);
		++res->len;
	}
}

void	fill_exp_chars(t_result *res, const char type)
{
	char	*num_str;
	size_t	size_num_str;

	type == 'e' ? ft_strncat(res->result, "e", 1) :
				ft_strncat(res->result, "E", 1);
	++res->len;
	num_str = ft_itoa(ft_abs(res->lg_10));
	size_num_str = ft_strlen(num_str);
	res->lg_10 >= 0 ? ft_strncat(res->result, "+", 1) :
					ft_strncat(res->result, "-", 1);
	++res->len;
	if (ft_abs(res->lg_10) >= 0 && ft_abs(res->lg_10) <= 9)
	{
		ft_strncat(res->result, "0", 1);
		++res->len;
	}
	ft_strncat(res->result, num_str, size_num_str);
	res->len += size_num_str;
	free(num_str);
}

void	fill_fucking_e(t_result *res, t_prsng *tools, t_high *hp, int *prec)
{
	char	curr_nu;

	while ((curr_nu = mul_ret_overflow(hp, 10) + '0') == '0')
		;
	ft_strncat(res->result, &curr_nu, 1);
	++res->len;
	--*prec;
	add_point(res, tools);
	while ((*prec)-- >= 0 && !hp_is_zero(hp, 0))
	{
		curr_nu = mul_ret_overflow(hp, 10) + '0';
		ft_strncat(res->result, &curr_nu, 1);
		++res->len;
	}
}

void	fill_fucking_l_e(t_result *res, t_prsng *tools, t_highl *hp, int *prec)
{
	char	curr_nu;

	while ((curr_nu = mul_ret_loverflow(hp, 10) + '0') == '0')
		;
	ft_strncat(res->result, &curr_nu, 1);
	++res->len;
	--*prec;
	add_point(res, tools);
	while ((*prec)-- >= 0 && !hp_is_lzero(hp, 0))
	{
		curr_nu = mul_ret_loverflow(hp, 10) + '0';
		ft_strncat(res->result, &curr_nu, 1);
		++res->len;
	}
}

void	rewrite_e_result(t_result *res, t_prsng *tools, int prec)
{
	++res->lg_10;
	if (!(res->begin = ft_strnew(res->len)))
	{
		res->len = 0;
		return ;
	}
	res->len = 0;
	ft_strncpy(res->begin, --res->result, 1);
	++res->len;
	free(res->result);
	res->result = res->begin;
	add_point(res, tools);
	while (prec--)
	{
		ft_strncat(res->result, "0", 1);
		++res->len;
	}
	fill_exp_chars(res, tools->type);
}
