/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zeroing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umoff <umoff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 13:47:54 by umoff             #+#    #+#             */
/*   Updated: 2020/07/02 13:29:34 by umoff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ptintf.h"

void	zeroing_tools(t_prsng *tools, _Bool zeroing_counter)
{
	size_t i;

	tools->flags = 0;
	tools->field = 0;
	tools->prec = -1;
	tools->mdfirs = 0;
	tools->type = 0;
	if (zeroing_counter)
	{
		tools->str_spf = NULL;
		tools->counter = 0;
		i = 0;
		while (i++ < BUFF_SIZE)
			tools->buff[i] = 0;
	}
}

void	zeroing_mkfield(t_mkfld *fld)
{
	fld->base = 0;
	fld->len = 0;
	fld->len_empty_field = 0;
	fld->lennum = 0;
	fld->nmbr.i = 0;
	fld->str = NULL;
}
