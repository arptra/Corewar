/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umoff <umoff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 13:37:11 by umoff             #+#    #+#             */
/*   Updated: 2020/07/02 14:04:17 by umoff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPTIONS_H
# define OPTIONS_H

# include "op.h"
# include <stdint.h>

# define MAX_COMMANDS 16

typedef struct	s_op
{
	char		*name;
	int			num_args;
	t_arg_type	args_type[3];
	u_int8_t	code;
	int			cycle;
	_Bool		argument_type_code;
	u_int8_t	size_t_dir;
}				t_op;

static t_op		g_op[17] = {
	{"live", 1, {T_DIR, 0, 0}, 1, 10, 0, DIR_LONG_LEN},
	{"ld", 2, {T_DIR | T_IND, T_REG, 0}, 2, 5, 1, DIR_LONG_LEN},
	{"st", 2, {T_REG, T_IND | T_REG, 0}, 3, 5, 1, DIR_LONG_LEN},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, 1, DIR_LONG_LEN},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, 1, DIR_LONG_LEN},
	{
		"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG},
		6, 6, 1, DIR_LONG_LEN
	},
	{
		"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},
		7, 6, 1, DIR_LONG_LEN
	},
	{
		"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},
		8, 6, 1, DIR_LONG_LEN
	},
	{"zjmp", 1, {T_DIR, 0, 0}, 9, 20, 0, DIR_SHRT_LEN},
	{
		"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},
		10, 25, 1, DIR_SHRT_LEN
	},
	{
		"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG},
		11, 25, 1, DIR_SHRT_LEN
	},
	{"fork", 1, {T_DIR, 0, 0}, 12, 800, 0, DIR_SHRT_LEN},
	{"lld", 2, {T_DIR | T_IND, T_REG, 0}, 13, 10, 1, DIR_LONG_LEN},
	{
		"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},
		14, 50, 1, DIR_SHRT_LEN
	},
	{"lfork", 1, {T_DIR, 0, 0}, 15, 1000, 0, DIR_SHRT_LEN},
	{"aff", 1, {T_REG, 0, 0}, 16, 2, 1, DIR_LONG_LEN},
	{0, 0, {0}, 0, 0, 0, 0}
};

#endif
