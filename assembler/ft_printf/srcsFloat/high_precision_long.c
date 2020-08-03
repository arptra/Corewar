/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   high_precision_long.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umoff <umoff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 14:14:39 by umoff             #+#    #+#             */
/*   Updated: 2020/07/02 13:31:44 by umoff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "high_precision.h"

static void	fill_data_lbits(t_highl *hp, int32_t big_shift, uint32_t res_high,
							uint32_t res_low)
{
	uint32_t	high_ind;

	if (hp->intg)
	{
		high_ind = ARRSIZE_INTG_LDBL - 1 - big_shift;
		if (high_ind < ARRSIZE_INTG_LDBL)
			hp->data_intg[high_ind] |= res_high;
		if (high_ind + 1 < ARRSIZE_INTG_LDBL)
			hp->data_intg[high_ind + 1] |= res_low;
	}
	else
	{
		high_ind = ARRSIZE_FRCT_LDBL - 1 - big_shift;
		if (high_ind < ARRSIZE_FRCT_LDBL)
			hp->data_frct[high_ind] |= res_high;
		if (high_ind + 1 < ARRSIZE_FRCT_LDBL)
			hp->data_frct[high_ind + 1] |= res_low;
	}
}

void		insert_low_lbits(t_highl *hp, uint32_t value, int32_t shift_amount,
							_Bool intg)
{
	int32_t		sub_shift;
	int32_t		big_shift;
	uint64_t	result;
	uint32_t	res_low;
	uint32_t	res_high;

	if (shift_amount <= 0)
		return ;
	sub_shift = shift_amount & (hp->word_shift - 1);
	big_shift = shift_amount / hp->word_shift;
	result = (uint64_t)value << sub_shift;
	res_low = (uint32_t)result;
	res_high = result >> hp->word_shift;
	if (intg)
		hp->intg = 1;
	else
		hp->intg = 0;
	fill_data_lbits(hp, big_shift, res_high, res_low);
}

void		insert_top_lbits(t_highl *hp, uint32_t value, int shift_amount,
							_Bool intg)
{
	insert_low_lbits(hp, value,
			(ARRSIZE_FRCT_LDBL + 1) * hp->word_shift - shift_amount, intg);
}

uint32_t	div_ret_lremainder(t_highl *hp, uint32_t divisor)
{
	uint32_t	remainder;
	ssize_t		i;
	uint64_t	dividend;
	uint64_t	result;

	remainder = 0;
	i = -1;
	while (++i < ARRSIZE_INTG_LDBL)
	{
		dividend = ((uint64_t)remainder << hp->word_shift) + hp->data_intg[i];
		result = dividend / divisor;
		remainder = (uint32_t)(dividend % divisor);
		hp->data_intg[i] = (uint32_t)result;
	}
	return (remainder);
}

uint32_t	mul_ret_loverflow(t_highl *hp, uint32_t multipl)
{
	uint32_t	owerflow;
	ssize_t		i;
	uint64_t	result;

	owerflow = 0;
	i = ARRSIZE_FRCT_LDBL;
	while (--i >= 0)
	{
		result = (uint64_t)multipl * hp->data_frct[i] + owerflow;
		hp->data_frct[i] = (uint32_t)result;
		owerflow = (uint32_t)(result >> hp->word_shift);
	}
	return (owerflow);
}
