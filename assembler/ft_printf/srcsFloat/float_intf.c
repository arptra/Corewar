/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_intf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umoff <umoff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 14:15:40 by umoff             #+#    #+#             */
/*   Updated: 2020/07/02 13:29:49 by umoff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "high_precision.h"

void		add_point(t_result *res, t_prsng *tools)
{
	if (tools->prec || tools->flags & M_PRECISION_NOT_ADDED ||
	tools->flags & M_SHARP)
	{
		ft_strncat(res->result, ".", 1);
		++res->len;
	}
}

char		*calculate_g_a_result(t_prsng *tools, t_mkfld *fld, int lg_10)
{
	char		*res;
	int			prec;

	res = NULL;
	if (ft_tolower(tools->type) == 'g')
	{
		if (!tools->prec && tools->flags & M_PRECISION_NOT_ADDED)
			tools->prec = 6;
		prec = (tools->prec) ? tools->prec : 1;
		if (!(res = get_g_result(tools, fld, lg_10)))
			return (NULL);
		if (tools->prec || tools->flags & M_PRECISION_NOT_ADDED ||
		tools->flags & M_SHARP)
			if (!(res = delete_lst_zeroes(res, fld, tools->type)))
				return (NULL);
		if (!(res = prepare_to_round(res, prec, fld, tools)))
			return (NULL);
	}
	return (res);
}
