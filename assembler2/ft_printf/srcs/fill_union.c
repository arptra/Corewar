/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_union.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umoff <umoff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 13:44:06 by umoff             #+#    #+#             */
/*   Updated: 2020/07/02 13:25:46 by umoff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ptintf.h"

void	fill_union_diouxx(t_mkfld *field, t_prsng *tools)
{
	field->nmbr.ull = 0;
	if (tools->mdfirs == 0 && tools->type == 'u')
		field->nmbr.ui = va_arg(tools->ap, unsigned int);
	else if (tools->mdfirs == 0)
		field->nmbr.i = va_arg(tools->ap, int);
	else if (tools->mdfirs & M_LL && tools->type == 'u')
		field->nmbr.ull = va_arg(tools->ap, unsigned long long);
	else if (tools->mdfirs & M_LL)
		field->nmbr.ll = va_arg(tools->ap, long long);
	else if (tools->mdfirs & M_L && tools->type == 'u')
		field->nmbr.ul = va_arg(tools->ap, unsigned long);
	else if (tools->mdfirs & M_L)
		field->nmbr.l = va_arg(tools->ap, long);
	else if (tools->mdfirs & M_H && tools->type == 'u')
		field->nmbr.ush = (unsigned short)va_arg(tools->ap, unsigned int);
	else if (tools->mdfirs & M_H)
		field->nmbr.sh = (short)va_arg(tools->ap, int);
	else if (tools->mdfirs & M_HH && tools->type == 'u')
		field->nmbr.uc = (unsigned char)va_arg(tools->ap, unsigned int);
	else if (tools->mdfirs & M_HH)
		field->nmbr.c = (char)va_arg(tools->ap, int);
}

_Bool	fill_union_csp(t_mkfld *field, t_prsng *tools)
{
	field->nmbr.ull = 0;
	if (tools->type == 'c')
	{
		if ((field->nmbr.c = (char)va_arg(tools->ap, int)) == 0)
			tools->flags |= M_ZERO_CHAR;
	}
	else if (tools->type == 's')
	{
		field->nmbr.cptr = va_arg(tools->ap, char*);
		if (!field->nmbr.cptr && !(field->nmbr.cptr = ft_strdup("(null)")))
			return (0);
	}
	else if (tools->type == 'p')
		field->nmbr.ull = va_arg(tools->ap, unsigned long long);
	return (1);
}

void	fill_union_aaeeffgg(t_mkfld *field, t_prsng *tools)
{
	field->nmbr.db = 0.0;
	field->nmbr.ldb = 0.0;
	if (tools->mdfirs & M_UPPER_L)
		field->nmbr.ldb = va_arg(tools->ap, long double);
	else
		field->nmbr.db = va_arg(tools->ap, double);
}
