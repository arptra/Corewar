/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_flags.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umoff <umoff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 13:45:22 by umoff             #+#    #+#             */
/*   Updated: 2020/07/02 13:29:18 by umoff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ptintf.h"

void	set_hex_prefix(t_mkfld *field, t_prsng *tools)
{
	if (tools->flags & M_B)
		;
	else if (tools->flags & M_SHARP && tools->type == 'o' &&
	field->lennum >= (size_t)tools->prec &&
	which_sign(&field->nmbr, tools) != 0)
	{
		field->str[field->len - 1] = '0';
		field->len--;
	}
	else if ((tools->flags & M_SHARP) && !(tools->flags & M_ZERO) &&
			(((tools->type == 'x' || tools->type == 'X') && field->nmbr.i)))
	{
		field->str[field->len - 2] = '0';
		field->str[field->len - 1] = tools->type;
		field->len -= 2;
	}
	else if (tools->type == 'p')
	{
		ft_strncpy(&field->str[field->len - 2], "0x", 2);
		field->len -= 2;
	}
}

void	set_sign(t_mkfld *field, t_prsng *tools)
{
	if (!(tools->flags & M_B) && tools->flags & M_PLUS && is_signed(tools->type)
	&& which_sign(&field->nmbr, tools) >= 0)
		field->str[--field->len] = '+';
	else if (!(tools->flags & M_B) && is_signed(tools->type) &&
	which_sign(&field->nmbr, tools) < 0)
		field->str[--field->len] = '-';
	else if (tools->flags & M_SPACE && is_signed(tools->type))
		field->str[--field->len] = ' ';
}

void	set_flags(t_mkfld *field, t_prsng *tools)
{
	set_hex_prefix(field, tools);
	if (tools->flags & M_ZERO && !(tools->flags & M_B))
	{
		while (field->len)
			field->str[--field->len] = '0';
		if ((tools->flags & M_PLUS && field->nmbr.i >= 0) ||
			which_sign(&field->nmbr, tools) < 0 || tools->flags & M_SPACE)
			field->len++;
	}
	if (!(tools->flags & M_B) && (tools->flags & M_SHARP &&
	(tools->flags & M_ZERO) != 0 && ((tools->type == 'x' || tools->type == 'X')
	&& field->nmbr.i)))
	{
		field->str[0] = '0';
		field->str[1] = tools->type;
		field->len -= 2;
	}
	set_sign(field, tools);
}
