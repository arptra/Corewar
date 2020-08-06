/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_log2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umoff <umoff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 14:15:21 by umoff             #+#    #+#             */
/*   Updated: 2020/07/02 13:30:01 by umoff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_float.h"

double	ft_log2(long double num)
{
	uint64_t	*dbl;
	int32_t		exp;
	long double	pow;

	dbl = (uint64_t *)&num;
	exp = get_lexp(dbl) - 16383;
	pow = ft_pow(2, exp);
	return (exp + ((num - pow) / pow));
}
