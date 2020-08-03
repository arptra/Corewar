/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   field_len.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umoff <umoff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 13:43:59 by umoff             #+#    #+#             */
/*   Updated: 2020/07/02 13:25:41 by umoff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ptintf.h"

size_t	count_lennum(t_mkfld *field, t_prsng *tools)
{
	size_t				lennum;
	unsigned long long	number;

	if (which_sign(&field->nmbr, tools) == 0)
		return (1);
	number = reverse_if_negative(&field->nmbr, tools);
	lennum = 1;
	while (number /= field->base)
		lennum++;
	return (lennum);
}

int		define_base(t_prsng *tools)
{
	if (tools->type == 'd' || tools->type == 'i' || tools->type == 'u' ||
		tools->type == 'f' || tools->type == 'F' || tools->type == 'e' ||
		tools->type == 'E' || tools->type == 'g' || tools->type == 'G')
		return (10);
	else if (tools->type == 'o')
		return (8);
	else
		return (16);
}

int		define_flaglen(t_mkfld *fld, t_prsng *tls)
{
	int len;

	len = 0;
	if (tls->flags & M_SHARP || tls->type == 'p')
	{
		if (tls->type == 'o')
		{
			if (!tls->prec && !(tls->flags & M_PRECISION_NOT_ADDED) &&
				!which_sign(&fld->nmbr, tls))
				;
			else if (fld->lennum >= (size_t)tls->prec &&
			(which_sign(&fld->nmbr, tls) ||
			!(tls->flags & M_PRECISION_NOT_ADDED)))
				len++;
		}
		else if (((tls->type == 'x' || tls->type == 'X') && fld->nmbr.i) ||
		tls->type == 'p')
			len = 2;
	}
	if ((tls->flags & M_SPACE && is_signed(tls->type)) ||
		(!(tls->flags & M_B) && ((tls->flags & M_PLUS &&
		which_sign(&fld->nmbr, tls) >= 0 && is_signed(tls->type)) ||
		(is_signed(tls->type) && which_sign(&fld->nmbr, tls) < 0))))
		len++;
	return (len);
}

void	len_counting_diouxxcsp(t_prsng *tools, t_mkfld *field)
{
	if ((tools->prec > 0 && (size_t)tools->prec > field->lennum)
		&& tools->type != 's'
		&& tools->type != 'c')
		field->len += tools->prec - field->lennum;
	field->len += define_flaglen(field, tools);
	if (tools->field > field->lennum + field->len)
		field->len_empty_field = tools->field - field->lennum - field->len;
	field->len += field->len_empty_field;
}
