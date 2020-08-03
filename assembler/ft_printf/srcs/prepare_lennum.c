/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_lennum.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umoff <umoff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 13:45:09 by umoff             #+#    #+#             */
/*   Updated: 2020/07/02 13:28:46 by umoff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ptintf.h"

void	get_lennum_binary_diouxx(t_prsng *tools, t_mkfld *field)
{
	if (tools->type == 'c')
		field->lennum = sizeof(char) * 8;
	else if (tools->mdfirs == 0)
		field->lennum = sizeof(int) * 9 - 1;
	else if (tools->mdfirs & M_LL)
		field->lennum = sizeof(long long) * 9 - 1;
	else if (tools->mdfirs & M_L)
		field->lennum = sizeof(long) * 9 - 1;
	else if (tools->mdfirs & M_H)
		field->lennum = sizeof(short) * 9 - 1;
	else if (tools->mdfirs & M_HH)
		field->lennum = sizeof(char) * 9 - 1;
}

void	diouxxcsp_lennum(t_prsng *tools, t_mkfld *field)
{
	if (tools->flags & M_B)
		get_lennum_binary_diouxx(tools, field);
	else if (tools->type && (tools->type == 'c' || !is_flag(tools->type)))
		field->lennum = 1;
	else if (((is_ddioouuxx(tools->type) && tools->type != 'o' &&
	!which_sign(&field->nmbr, tools)) || tools->type == 'p') &&
	(!tools->prec && !(tools->flags & M_PRECISION_NOT_ADDED)))
		field->lennum = 0;
	else if (tools->type == 'o' && !(tools->flags & M_SHARP) &&
	(!tools->prec && !(tools->flags & M_PRECISION_NOT_ADDED)))
		field->lennum = 0;
	else if (tools->type == 's')
	{
		field->lennum = ft_strlen(field->nmbr.cptr);
		if (field->lennum > (size_t)tools->prec &&
			!(tools->flags & M_PRECISION_NOT_ADDED))
			field->lennum = tools->prec;
	}
	else if (is_ddioouuxx(tools->type) || tools->type == 'p')
		field->lennum = count_lennum(field, tools);
}

void	aaeeffgg_lennum_len(t_prsng *tools, t_mkfld *field)
{
	if (*field->str == '-' || *field->str == '0')
		field->lennum = ft_strlen(field->str);
	if (field->lennum < tools->field)
		field->len = tools->field - field->lennum;
	else if (!ft_isalpha(*field->str) && *field->str != '-' &&
	field->lennum >= tools->field && (tools->flags & M_SPACE ||
	tools->flags & M_PLUS || which_sign(&field->nmbr, tools) < 0))
		field->len++;
}
