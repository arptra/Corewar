/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_field.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umoff <umoff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 13:44:52 by umoff             #+#    #+#             */
/*   Updated: 2020/07/02 13:26:16 by umoff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ptintf.h"

int		prepare_diouxxcsp(t_prsng *tools, t_mkfld *field)
{
	if (is_ddioouuxx(tools->type))
		fill_union_diouxx(field, tools);
	else if (is_csp(tools->type))
		if (!fill_union_csp(field, tools))
			return (0);
	field->base = define_base(tools);
	diouxxcsp_lennum(tools, field);
	len_counting_diouxxcsp(tools, field);
	return (1);
}

int		prepare_aaeeffgg(t_prsng *tls, t_mkfld *fld)
{
	fill_union_aaeeffgg(fld, tls);
	if (!(tls->flags & M_B))
	{
		if ((tls->mdfirs & M_UPPER_L))
			fld->str = print_long_double(tls, fld, fld->nmbr.ldb);
		else
			fld->str = print_double(tls, fld, fld->nmbr.db);
	}
	else
	{
		fld->lennum = 2 +
				(((tls->mdfirs & M_UPPER_L)) ? 80 : (sizeof(double) * 8));
		if (tls->mdfirs & M_UPPER_L)
			fld->str = get_binary((uint64_t *)&fld->nmbr.ldb, 80, fld, 'd');
		else
			fld->str = get_binary((uint64_t *)&fld->nmbr.db,
						sizeof(double) * 8, fld, 'f');
	}
	if (!fld->str)
		return (0);
	aaeeffgg_lennum_len(tls, fld);
	return (1);
}

int		diouxx(t_prsng *tools, t_mkfld *field)
{
	if (!prepare_diouxxcsp(tools, field))
		return (0);
	if (tools->type && !set_buff(field, tools))
	{
		if (tools->type == 's' && !ft_strcmp("(null)", field->nmbr.cptr))
			free(field->nmbr.cptr);
		return (0);
	}
	if (tools->type == 's' && !ft_strcmp("(null)", field->nmbr.cptr))
		free(field->nmbr.cptr);
	return (1);
}

int		organozation_by_flags_to_buff(t_prsng *tools)
{
	t_mkfld field;

	zeroing_mkfield(&field);
	if (is_aaeeffgg(tools->type))
	{
		if (!prepare_aaeeffgg(tools, &field))
			return (2);
		if (!set_buff_float(&field, tools))
		{
			free(field.str);
			return (0);
		}
	}
	else
		diouxx(tools, &field);
	free(field.str);
	return (1);
}
