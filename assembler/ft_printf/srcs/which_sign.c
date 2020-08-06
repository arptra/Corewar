/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   which_sign.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umoff <umoff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 13:47:49 by umoff             #+#    #+#             */
/*   Updated: 2020/07/02 13:29:29 by umoff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ptintf.h"

int		which_sign_aaeeffgg(t_un *number, t_prsng *tools)
{
	if ((tools->mdfirs == 0 && number->i < 0) ||
		(tools->mdfirs & M_L && number->l < 0) ||
		(tools->mdfirs & M_H && number->sh < 0) ||
		(tools->mdfirs & M_LL && number->ll < 0) ||
		(tools->mdfirs & M_HH && number->c < 0))
		return (-1);
	else if ((tools->mdfirs == 0 && number->i > 0) ||
			(tools->mdfirs & M_L && number->l > 0) ||
			(tools->mdfirs & M_H && number->sh > 0) ||
			(tools->mdfirs & M_LL && number->ll > 0) ||
			(tools->mdfirs & M_HH && number->c > 0))
		return (1);
	return (0);
}

int		which_sign(t_un *number, t_prsng *tools)
{
	if (!is_aaeeffgg(tools->type))
		return (which_sign_aaeeffgg(number, tools));
	else
	{
		if (((tools->mdfirs == 0 || tools->mdfirs & M_L)
			&& number->db < 0) ||
			(tools->mdfirs & M_UPPER_L && number->ldb < 0))
			return (-1);
		else if (((tools->mdfirs == 0 || tools->mdfirs & M_L)
					&& number->db > 0) ||
					(tools->mdfirs & M_UPPER_L && number->ldb > 0))
			return (1);
	}
	return (0);
}
