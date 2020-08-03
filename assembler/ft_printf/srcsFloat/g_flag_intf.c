/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_flag_intf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umoff <umoff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 14:15:09 by umoff             #+#    #+#             */
/*   Updated: 2020/07/02 13:30:10 by umoff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_float.h"

char		*get_g_result(t_prsng *tools, t_mkfld *fld, int lg_10)
{
	char	*res;

	if ((lg_10 < -4 || lg_10 >= ((!tools->prec) ? 1 : tools->prec)))
		tools->type = (tools->type == 'g') ? 'e' : 'E';
	else
		tools->type = (tools->type == 'g') ? 'f' : 'F';
	if (tools->mdfirs & M_UPPER_L)
	{
		if (!(res = print_long_double(tools, fld, fld->nmbr.ldb)))
			return (NULL);
	}
	else if (!(res = print_double(tools, fld, fld->nmbr.db)))
		return (NULL);
	return (res);
}

char		*delete_lst_zeroes(char *res, t_mkfld *fld, const char type)
{
	size_t	i;
	char	*res_only_sign;
	char	*lst_d;
	char	*first_d;
	size_t	delta;

	i = fld->lennum;
	if (ft_tolower(type) == 'e')
		while (*(res + --i) != 'e')
			;
	lst_d = res + i;
	while (*(res + --i) == '0')
		;
	first_d = res + i;
	delta = lst_d - first_d - 1;
	if (!(res_only_sign = ft_strnew(fld->lennum - delta)))
		return (NULL);
	ft_strncpy(res_only_sign, res, i + 1);
	ft_strncat(res_only_sign, lst_d, res + fld->lennum - lst_d);
	free(res);
	fld->lennum -= delta;
	return (res_only_sign);
}

static int	last_char_prec(char *res, int prec, int *sign_cnt)
{
	int	i;
	int	lst_i;

	i = 0;
	*sign_cnt = 0;
	while (*sign_cnt != prec)
	{
		if (ft_tolower(*(res + i++)) == 'e')
			break ;
		if (*(res + i) != '.')
			++*sign_cnt;
	}
	lst_i = i;
	while (*(res + lst_i) && ft_tolower(*(res + lst_i)) != 'e')
	{
		++lst_i;
		++*sign_cnt;
	}
	return (i);
}

static char	*trunc_dgt(char *res, int prec, size_t lennum, const char type)
{
	int		i;
	char	*trunc_res;
	int		sign_cnt;

	i = last_char_prec(res, prec, &sign_cnt);
	if (!(trunc_res = ft_strnew(lennum)))
		return (NULL);
	ft_strncpy(trunc_res, res, i);
	if (ft_tolower(type) == 'e')
	{
		i = lennum;
		while (*(res + --i) != 'e')
			;
		ft_strncat(trunc_res, res + i, res + lennum - (res + i));
	}
	free(res);
	return (trunc_res);
}

char		*prepare_to_round(char *res, int prec, t_mkfld *fld, t_prsng *tools)
{
	int			sign_cnt;
	int			lst_i;
	t_result	rnd_res;
	char		nxt_chr;

	lst_i = last_char_prec(res, prec, &sign_cnt);
	nxt_chr = *(res + lst_i);
	res = trunc_dgt(res, prec, fld->lennum, tools->type);
	if (sign_cnt > prec && ft_isdigit(nxt_chr) && nxt_chr >= '5')
	{
		fld->lennum = ft_strlen(res);
		if (!(rnd_res.result = ft_strnew(fld->lennum + 1)))
			return (NULL);
		*rnd_res.result = '0';
		ft_strncpy(++rnd_res.result, res, fld->lennum);
		rnd_res.begin = rnd_res.result - 1;
		rnd_res.len = fld->lennum;
		float_round(&rnd_res, nxt_chr - '0');
		free(res);
		check_result(&rnd_res, tools, prec, fld);
		if (!rnd_res.len)
			return (NULL);
		res = delete_lst_zeroes(rnd_res.result, fld, tools->type);
	}
	return (res);
}
