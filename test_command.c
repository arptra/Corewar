/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umoff <umoff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 13:37:34 by umoff             #+#    #+#             */
/*   Updated: 2020/07/02 14:03:21 by umoff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

/*
** Функция проверки аргументов
*/

void	check_args(t_tkn *tkn, int *i, int com_code)
{
	t_tkn	*tkn_arg;
	t_arg	*arg;

	tkn_arg = tkn->next;
	while (tkn_arg && tkn_arg->type != NEW_LINE)
	{
		if (tkn_arg->type == ARGUMENT || tkn_arg->type == ARGUMENT_LABEL)
		{
			arg = (t_arg*)tkn_arg->content;
			if (!(arg->type & ((g_op[com_code]).args_type[*i])))
				tkn_error(ERR_ARGS, tkn_arg, 0);
			(*i)++;
		}
		else if (tkn_arg->type == COMMENT && tkn_arg->next &&
				tkn_arg->next->type == NEW_LINE)
			return ;
		else if (tkn_arg->type != SEPARATOR)
			tkn_error(ERR_ARGS, tkn_arg, 0);
		tkn_arg = tkn_arg->next;
	}
}

/*
** Функция проверки команды 
*/

void	test_command(t_tkn *tkn)
{
	int			i;
	u_int8_t	com_code;

	i = 0;
	if (!(tkn->type == COMMAND))
		return ;
	com_code = *(u_int8_t *)tkn->content - 1;
	check_args(tkn, &i, com_code);
	if ((i < 2 && ((g_op[com_code]).args_type[1] != 0))
		|| (i < 3 && ((g_op[com_code]).args_type[2] != 0)))
		tkn_error(ERR_ARGS, tkn, 0);
}
