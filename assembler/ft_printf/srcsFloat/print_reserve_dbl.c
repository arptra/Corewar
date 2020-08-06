/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_reserve_dbl.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umoff <umoff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 14:14:15 by umoff             #+#    #+#             */
/*   Updated: 2020/07/02 13:31:56 by umoff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_float.h"

char		*print_nan(t_result *res, const char type)
{
	if (!(res->result = ft_strnew(3)))
	{
		res->len = 0;
		return (NULL);
	}
	if (type == 'F')
		return (ft_strcpy(res->result, "NAN"));
	return (ft_strcpy(res->result, "nan"));
}

char		*print_inf(t_result *res, _Bool sign, const char type)
{
	if (!(res->result = ft_strnew(4)))
	{
		res->len = 0;
		return (NULL);
	}
	if (type == 'F')
	{
		return (sign ?
				ft_strcpy(res->result, "-INf") : ft_strcpy(res->result, "INf"));
	}
	return (sign ?
			ft_strcpy(res->result, "-inf") : ft_strcpy(res->result, "inf"));
}

static void	fill_reserve_zero(t_prsng *tools, t_result *res)
{
	if (!tools->prec && tools->flags & M_PRECISION_NOT_ADDED)
		tools->prec = 6;
	if (tools->prec || tools->flags & M_PRECISION_NOT_ADDED ||
		tools->flags & M_SHARP)
		ft_strncat(res->result, ".", 1);
	while (tools->prec-- > 0)
		ft_strncat(res->result, "0", 1);
}

char		*print_zero(t_result *res, _Bool sign, t_prsng *tools)
{
	if (ft_tolower(tools->type) == 'f')
	{
		if (!(res->result = ft_strnew(2)))
		{
			res->len = 0;
			return (NULL);
		}
	}
	else if (ft_tolower(tools->type) == 'e')
		if (!(res->result = ft_strnew(13)))
		{
			res->len = 0;
			return (NULL);
		}
	sign ? ft_strcpy(res->result, "-0") : ft_strcpy(res->result, "0");
	fill_reserve_zero(tools, res);
	if (ft_tolower(tools->type) == 'e')
	{
		res->lg_10 = 0;
		fill_exp_chars(res, tools->type);
	}
	return (res->result);
}
