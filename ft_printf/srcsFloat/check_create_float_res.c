/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_create_float_res.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umoff <umoff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 14:15:48 by umoff             #+#    #+#             */
/*   Updated: 2020/07/02 13:29:41 by umoff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_float.h"
#include "libft.h"

static size_t	len_log(int32_t lg_10)
{
	size_t	len;

	len = (lg_10 < 0) ? 2 : 1;
	while (lg_10 /= 10)
		++len;
	return (len);
}

static void		create_for_e(t_prsng *tls, size_t *lennum, const int32_t lg_10)
{
	if (tls->prec)
		*lennum = 1 + tls->prec;
	else if (tls->flags & M_PRECISION_NOT_ADDED)
	{
		*lennum = 1 + 6;
		tls->prec = 6;
	}
	else
		*lennum = 1;
	if (tls->flags & M_SHARP || tls->prec || tls->flags & M_PRECISION_NOT_ADDED)
		++*lennum;
	if (lg_10 >= 0)
	{
		if (lg_10 >= 0 && lg_10 <= 9)
			*lennum += 1 + len_log(lg_10) + 1 + 1;
		else
			*lennum += 1 + len_log(lg_10) + 1;
	}
	else
	{
		if (ft_abs(lg_10) >= 0 && ft_abs(lg_10) <= 9)
			*lennum += 1 + len_log(lg_10) + 1;
		else
			*lennum += 1 + len_log(lg_10);
	}
}

static void		create_for_f(t_prsng *tls, size_t *lennum, const int32_t lg_10)
{
	if (tls->prec)
		*lennum = (lg_10 > 0) ? lg_10 + 1 + tls->prec : 1 + tls->prec;
	else if (tls->flags & M_PRECISION_NOT_ADDED)
	{
		*lennum = (lg_10 > 0) ? lg_10 + 1 + 6 : 1 + 6;
		tls->prec = 6;
	}
	else
		*lennum = (lg_10 > 0) ? lg_10 + 1 : 1;
	if (tls->flags & M_SHARP || tls->prec ||
			tls->flags & M_PRECISION_NOT_ADDED)
		++*lennum;
}

t_result		create_str(const int32_t lg_10, t_prsng *tools, t_mkfld *fld)
{
	t_result	res;
	size_t		lennum;

	if (tools->type == 'e' || tools->type == 'E')
		create_for_e(tools, &lennum, lg_10);
	else if (tools->type == 'f' || tools->type == 'F')
		create_for_f(tools, &lennum, lg_10);
	res.buff = ft_strnew(ft_abs(lg_10));
	if (!res.buff || !(res.result = ft_strnew(lennum + 1)))
		return ((t_result){NULL, NULL, 0, 0, NULL, 0});
	*res.result = '0';
	res.begin = res.result;
	++res.result;
	fld->lennum = lennum;
	res.lg_10 = lg_10;
	return (res);
}

void			check_result(t_result *res, t_prsng *tools, int prec,
						t_mkfld *fld)
{
	if (res->result != res->begin)
	{
		if (*res->begin != '0')
		{
			if ((tools->type == 'e' || tools->type == 'E'))
				rewrite_e_result(res, tools, prec);
			else
			{
				--res->result;
				++res->len;
			}
		}
		else
		{
			if (!(res->begin = ft_strnew(res->len)))
			{
				res->len = 0;
				return ;
			}
			ft_strncpy(res->begin, res->result, res->len);
			free(--res->result);
			res->result = res->begin;
		}
	}
	fld->lennum = res->len;
}
