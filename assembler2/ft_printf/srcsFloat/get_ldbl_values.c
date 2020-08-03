/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ldbl_values.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umoff <umoff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 14:14:59 by umoff             #+#    #+#             */
/*   Updated: 2020/07/02 13:30:19 by umoff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_float.h"

_Bool		get_lsign(uint64_t *ldbl)
{
	return (*(ldbl + 1) & (1 << 15));
}

int32_t		get_lexp(uint64_t *ldbl)
{
	return (*(ldbl + 1) & 0x7FFF);
}

uint64_t	get_lmantissa(uint64_t *ldbl)
{
	return (*ldbl & 0xFFFFFFFFFFFFFFFF);
}
