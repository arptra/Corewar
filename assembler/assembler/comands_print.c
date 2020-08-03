/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comands_print.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umoff <umoff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 13:42:58 by umoff             #+#    #+#             */
/*   Updated: 2020/07/02 14:01:54 by umoff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

/*
** Функция вычисления кода типа аргумента
*/

u_int8_t	calc_arg_type_code(t_tkn *tkn)
{
	u_int8_t		num_args;
	int				i;
	unsigned int	res;
	t_op			*op;

	i = 0;
	res = 0;
	op = &g_op[*(u_int8_t*)tkn->content - 1];
	num_args = op->num_args;
	while (num_args--)
	{
		while ((tkn->type != ARGUMENT && tkn->type != ARGUMENT_LABEL))
			tkn = tkn->next;
		if (((t_arg*)tkn->content)->type & T_REG)
			res |= REG_CODE << (i + 6);
		else if (((t_arg*)tkn->content)->type & T_IND)
			res |= IND_CODE << (i + 6);
		else if (((t_arg*)tkn->content)->type & T_DIR)
			res |= DIR_CODE << (i + 6);
		tkn = tkn->next;
		i -= 2;
	}
	return (res);
}

/*
** Функция записи в обратном порядке 
*/

void		write_reverse(t_tkn *tkn, t_op *op, int fd)
{
	u_int32_t		*p32;
	u_int8_t		*p8;

	p32 = (u_int32_t*)&((t_arg*)tkn->content)->num;
	p8 = (u_int8_t*)p32;
	if (((t_arg*)tkn->content)->type & T_DIR)
	{
		if (op->size_t_dir == DIR_LONG_LEN)
		{
			write(fd, &p8[3], 1);
			write(fd, &p8[2], 1);
		}
	}
	write(fd, &p8[1], 1);
	write(fd, &p8[0], 1);
}

/*
** Функция печати аргументов 
*/

void		print_args(int fd, t_tkn *tkn)
{
	t_op			*op;
	u_int8_t		res8;
	u_int8_t		num_args;

	op = &g_op[*(u_int8_t*)tkn->content - 1];
	num_args = op->num_args;
	while (num_args--)
	{
		while ((tkn->type != ARGUMENT && tkn->type != ARGUMENT_LABEL))
			tkn = tkn->next;
		if (((t_arg*)tkn->content)->type & T_REG)
		{
			res8 = (u_int8_t)((t_arg*)tkn->content)->num;
			write(fd, &res8, 1);
		}
		else
			write_reverse(tkn, op, fd);
		tkn = tkn->next;
	}
}

/*
** Функция печати команд 
*/

void		commands_print(int fd, t_tkn *tkn)
{
	unsigned char	res;
	int				com_code;

	while (tkn->next != NULL)
	{
		if (tkn->type == COMMAND)
		{
			com_code = *(u_int8_t *)tkn->content - 1;
			write(fd, &g_op[com_code].code, 1);
			if (g_op[com_code].argument_type_code)
			{
				res = calc_arg_type_code(tkn);
				write(fd, &res, 1);
			}
			print_args(fd, tkn);
		}
		tkn = tkn->next;
	}
}
