/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dbl_values.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umoff <umoff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 14:15:04 by umoff             #+#    #+#             */
/*   Updated: 2020/07/02 13:30:14 by umoff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_float.h"

_Bool		get_sign(uint64_t *dbl)
{
	return (*dbl >> 63);
}

int32_t		get_exp(uint64_t *dbl)
{
	return (*dbl >> 52 & 0x7FF);
}

uint64_t	get_mantissa(uint64_t *dbl)
{
	return (*dbl & (1LL << 52) - 1);
}
