/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base_printf.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umoff <umoff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 13:44:15 by umoff             #+#    #+#             */
/*   Updated: 2020/07/02 13:25:52 by umoff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ptintf.h"

unsigned long long	reverse_if_negative(t_un *number, t_prsng *tools)
{
	unsigned long long ret;

	ret = 0;
	if (!is_signed(tools->type) ||
		(is_signed(tools->type) && which_sign(number, tools) > 0))
		ret = number->ull;
	else
	{
		if (tools->mdfirs == 0)
			ret = -(unsigned long long)number->i;
		else if (tools->mdfirs & M_L)
			ret = -(unsigned long long)number->l;
		else if (tools->mdfirs & M_H)
			ret = -(unsigned long long)number->sh;
		else if (tools->mdfirs & M_LL)
			ret = -(unsigned long long)number->ll;
		else if (tools->mdfirs & M_HH)
			ret = -(unsigned long long)number->c;
	}
	return (ret);
}

char				*itoa_base_union(t_prsng *tools, t_mkfld *field, char *str)
{
	unsigned long long	n;
	size_t				lennum;

	lennum = field->lennum;
	n = reverse_if_negative(&field->nmbr, tools);
	while (lennum--)
	{
		str[lennum] = n % field->base + (n % field->base > 9 ? 'A' - 10 : '0');
		n /= field->base;
	}
	return (str);
}
