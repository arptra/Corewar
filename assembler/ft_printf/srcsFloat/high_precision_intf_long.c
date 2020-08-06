/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   high_precision_intf_long.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umoff <umoff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 14:14:52 by umoff             #+#    #+#             */
/*   Updated: 2020/07/02 13:31:39 by umoff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "high_precision.h"
#include "ft_ptintf.h"

t_highl		*hp_ldbl_initializ(void)
{
	t_highl	*new;

	if (!(new = (t_highl *)malloc(sizeof(t_highl))))
		return (NULL);
	ft_memcpy(new, &(t_highl){{0}, {0}, 32, 1}, sizeof(*new));
	return (new);
}

_Bool		hp_is_lzero(t_highl *hp, _Bool intg)
{
	size_t i;

	i = 0;
	if (intg)
	{
		while (i < ARRSIZE_INTG_LDBL)
			if (hp->data_intg[i++] != 0)
				return (0);
	}
	else
		while (i < ARRSIZE_FRCT_LDBL)
			if (hp->data_frct[i++] != 0)
				return (0);
	return (1);
}

static void	fill_lresult_fract(t_highl *hp, _Bool intg, t_prsng *tools,
							t_result *res)
{
	char	rem_overf;
	int		nxt_nu;
	int		prec;

	ft_memcpy(&prec, &tools->prec, sizeof(int));
	if (!*res->result && (tools->type == 'e' || tools->type == 'E'))
		fill_fucking_l_e(res, tools, hp, &prec);
	while (prec > 0 && !hp_is_lzero(hp, intg))
	{
		rem_overf = mul_ret_loverflow(hp, 10) + '0';
		ft_strncat(res->result, &rem_overf, 1);
		++res->len;
		--prec;
	}
	if (prec <= 0 && (nxt_nu = mul_ret_loverflow(hp, 10)) >= 5)
		float_round(res, nxt_nu);
	else
		while (prec-- > 0)
		{
			ft_strncat(res->result, "0", 1);
			++res->len;
		}
}

static void	fill_lresult_intg(t_highl *hp, _Bool intg, t_result *res, char type)
{
	char	rem_overf;

	rem_overf = div_ret_lremainder(hp, 10) + '0';
	ft_strncat(res->buff, &rem_overf, 1);
	++res->bf_len;
	while (!hp_is_lzero(hp, intg))
	{
		rem_overf = div_ret_lremainder(hp, 10) + '0';
		ft_strncat(res->buff, &rem_overf, 1);
		++res->bf_len;
	}
	ft_reverse(res->buff);
	if ((type == 'e' || type == 'E') && (res->bf_len > 1 || *res->buff == '0'))
		check_e_intg_res(res);
	else
	{
		ft_strncpy(res->result, res->buff, res->bf_len);
		res->len = res->bf_len;
		clear_res_buff(res);
	}
}

void		fill_lresult(t_highl *hp, _Bool intg, t_prsng *tls, t_result *rs)
{
	if (intg)
	{
		rs->len = 0;
		rs->bf_len = 0;
		fill_lresult_intg(hp, intg, rs, tls->type);
	}
	else
	{
		if (rs->buff)
		{
			while (++rs->buff && *rs->buff && tls->prec-- && ++rs->bf_len)
			{
				ft_strncat(rs->result, rs->buff, 1);
				++rs->len;
			}
			if (*rs->buff && *rs->buff >= '5')
				float_round(rs, *rs->buff - '0');
			else if (!*rs->buff)
				fill_lresult_fract(hp, intg, tls, rs);
			rs->buff -= rs->bf_len + 1;
			clear_res_buff(rs);
		}
		else
			fill_lresult_fract(hp, intg, tls, rs);
	}
}
