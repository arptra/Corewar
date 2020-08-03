/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umoff <umoff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/30 13:37:45 by umoff             #+#    #+#             */
/*   Updated: 2020/07/02 14:02:13 by umoff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "options.h"
#include "assembler.h"

/*
** Функция подсчета длины команды 
*/

u_int32_t	len_command(t_tkn *tkn)
{
	t_op		*op;
	uint32_t	lenth;
	u_int8_t	num_args;

	op = &g_op[*(u_int8_t*)tkn->content - 1];
	lenth = COMMAND_LEN;
	num_args = op->num_args;
	lenth += op->argument_type_code;
	while (num_args--)
	{
		while ((tkn->type != ARGUMENT && tkn->type != ARGUMENT_LABEL))
			tkn = tkn->next;
		if (((t_arg*)tkn->content)->type & T_REG)
			lenth += REG_LEN;
		else if (((t_arg*)tkn->content)->type & T_IND)
			lenth += IND_LEN;
		else if (((t_arg*)tkn->content)->type & T_DIR)
			lenth += op->size_t_dir;
		tkn = tkn->next;
	}
	return (lenth);
}
