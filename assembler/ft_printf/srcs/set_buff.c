/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_buff.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umoff <umoff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 13:45:16 by umoff             #+#    #+#             */
/*   Updated: 2020/07/02 13:28:53 by umoff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ptintf.h"

void	get_value_by_type(t_mkfld *fld, t_prsng *tls)
{
	if (tls->flags & M_B)
		get_binaryd_by_type(tls, fld);
	else if (((is_ddioouuxx(tls->type) && tls->type != 'o' &&
			!which_sign(&fld->nmbr, tls)) || tls->type == 's') &&
			(tls->prec == 0 && !(tls->flags & M_PRECISION_NOT_ADDED)))
		;
	else if (is_ddioouuxx(tls->type) || tls->type == 'p')
	{
		itoa_base_union(tls, fld, &fld->str[fld->len]);
		if (tls->type == 'x' || tls->type == 'p')
			str_tolower(&fld->str[fld->len]);
	}
	else if (tls->type == 's')
		ft_strncpy(&fld->str[fld->len], fld->nmbr.cptr, fld->lennum);
	else if (tls->type == 'c')
		fld->str[fld->len] = fld->nmbr.c;
	else if (!is_flag(tls->type))
		fld->str[fld->len] = tls->type;
}

_Bool	set_buff(t_mkfld *fld, t_prsng *tls)
{
	if (!(fld->str = (char*)malloc(sizeof(char) *
												(fld->lennum + fld->len + 1))))
		return (0);
	ft_memset(fld->str, ' ', fld->lennum + fld->len);
	fld->str[fld->lennum + fld->len] = '\0';
	if (tls->flags & M_MINUS)
		fld->len -= fld->len_empty_field;
	get_value_by_type(fld, tls);
	if (!(tls->flags & M_B) && tls->prec > 0 && fld->lennum &&
		(size_t)tls->prec > fld->lennum && tls->type != 's')
	{
		fld->len -= tls->prec - fld->lennum;
		ft_memset(&fld->str[fld->len], '0', tls->prec - fld->lennum);
	}
	set_flags(fld, tls);
	to_buff(fld->str, tls, fld);
	return (1);
}

void	set_value_float(t_mkfld *fld, t_prsng *tls, char *str)
{
	if (tls->flags & M_MINUS)
		fld->len_empty_field =
				((tls->flags & M_SPACE ||
				tls->flags & M_PLUS ||
				which_sign(&fld->nmbr, tls) < 0) ? 1 : 0);
	else
		fld->len_empty_field = fld->len;
	ft_strncpy(&str[fld->len_empty_field], fld->str, fld->lennum);
}

void	set_diouxx_sign(t_mkfld *fld, t_prsng *tls, char *str)
{
	if (!(tls->flags & M_B) && !ft_isalpha(*fld->str) && *fld->str != '-' &&
		which_sign(&fld->nmbr, tls) < 0)
		str[fld->len_empty_field - 1] = '-';
	else if (!(tls->flags & M_B) && !ft_isalpha(*fld->str) && *fld->str != '-'
			&& tls->flags & M_PLUS)
		str[fld->len_empty_field - 1] = '+';
	else if (tls->flags & M_SPACE)
		str[fld->len_empty_field - 1] = ' ';
}

_Bool	set_buff_float(t_mkfld *fld, t_prsng *tls)
{
	char *str;

	if (!(str = (char*)malloc(sizeof(char) * (fld->lennum + fld->len + 1))))
		return (0);
	ft_memset(str, ' ', fld->lennum + fld->len);
	str[fld->lennum + fld->len] = '\0';
	set_value_float(fld, tls, str);
	if (tls->flags & M_ZERO && !ft_isalpha(*fld->str) && *fld->str != '-' &&
			!(tls->flags & M_B))
	{
		ft_memset(str, '0', fld->len_empty_field);
		fld->len_empty_field = 1;
	}
	set_diouxx_sign(fld, tls, str);
	to_buff(str, tls, fld);
	free(str);
	if (tls->type == 's' && !ft_strcmp("(null)", fld->nmbr.cptr))
		free(fld->nmbr.cptr);
	return (1);
}
