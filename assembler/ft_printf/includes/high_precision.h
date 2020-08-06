/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   high_precision.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umoff <umoff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 14:16:03 by umoff             #+#    #+#             */
/*   Updated: 2020/07/02 13:23:52 by umoff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HIGH_PRECISION_H
# define HIGH_PRECISION_H

# define ARRSIZE_INTG_DBL 32
# define ARRSIZE_FRCT_DBL 34
# define ARRSIZE_INTG_LDBL 512
# define ARRSIZE_FRCT_LDBL 514
# include <stdlib.h>
# include <stdint.h>
# include "my_float.h"
# include "ft_ptintf.h"

typedef struct	s_high
{
	unsigned	data_intg[ARRSIZE_INTG_DBL];
	unsigned	data_frct[ARRSIZE_FRCT_DBL];
	const int	word_shift;
	_Bool		intg;
}				t_high;

typedef struct	s_highl
{
	unsigned	data_intg[ARRSIZE_INTG_LDBL];
	unsigned	data_frct[ARRSIZE_FRCT_LDBL];
	const int	word_shift;
	_Bool		intg;
}				t_highl;

t_high			*hp_initializ(void);
t_highl			*hp_ldbl_initializ(void);
_Bool			hp_is_zero(t_high *hp, _Bool intg);
_Bool			hp_is_lzero(t_highl *hp, _Bool intg);
void			insert_low_bits(t_high *hp, uint32_t value, int shift_amount,
								_Bool intg);
void			insert_low_lbits(t_highl *hp, uint32_t value,
		int32_t shift_amount, _Bool intg);
void			insert_top_bits(t_high *hp, uint32_t value, int shift_amount,
								_Bool intg);
void			insert_top_lbits(t_highl *hp, uint32_t value, int shift_amount,
								_Bool intg);
uint32_t		div_ret_remainder(t_high *hp, uint32_t divisor);
uint32_t		div_ret_lremainder(t_highl *hp, uint32_t divisor);
uint32_t		mul_ret_overflow(t_high *hp, uint32_t multipl);
uint32_t		mul_ret_loverflow(t_highl *hp, uint32_t multipl);
void			fill_result(t_high *hp, _Bool intg, t_prsng *tools,
							t_result *res);
void			fill_lresult(t_highl *hp, _Bool intg, t_prsng *tools,
							t_result *res);
void			fill_fucking_e(t_result *res, t_prsng *tools, t_high *hp,
							int *prec);
void			fill_fucking_l_e(t_result *res, t_prsng *tools, t_highl *hp,
							int *prec);
void			free_hp(t_high *hp);
void			free_l_hp(t_highl *hp);

#endif
