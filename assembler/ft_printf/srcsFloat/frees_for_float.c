/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees_for_float.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umoff <umoff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 14:15:28 by umoff             #+#    #+#             */
/*   Updated: 2020/07/02 13:29:57 by umoff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "high_precision.h"

void	clear_res_buff(t_result *res)
{
	free(res->buff);
	res->buff = NULL;
	res->bf_len = 0;
}

void	free_hp(t_high *hp)
{
	free(hp);
	hp = NULL;
}

void	free_l_hp(t_highl *hp)
{
	free(hp);
	hp = NULL;
}
