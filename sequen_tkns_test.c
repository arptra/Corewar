/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sequen_tkns_test.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umoff <umoff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/31 13:43:40 by umoff             #+#    #+#             */
/*   Updated: 2020/07/02 14:03:04 by umoff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "assembler.h"

/*
** Проверка если попалась строка
*/

void	this_string(t_tkn *tkn, t_tkn_sec *check_list)
{
	if (tkn->type == STRING)
	{
		tkn = tkn->prev;
		while (tkn && tkn->type == NEW_LINE)
			tkn = tkn->prev;
		if (!tkn || (tkn->type != STRING && tkn->type != NAME &&
												tkn->type != COMMENT_PROG))
			tkn_error(INVALID_STR_PLACE, tkn, 0);
		if (tkn->type == NAME)
			check_list->str_name = true;
		else if (tkn->type == COMMENT_PROG)
			check_list->str_comment = true;
	}
}

/*
** Функция установки команды 
*/

void	set_command(t_tkn *tkn, t_tkn_sec *check_list, char *com_name)
{
	int i;

	i = 0;
	check_list->new_line = false;
	check_list->command = true;
	check_list->arg = false;
	while (g_op[i].name && !ft_strequ(com_name, g_op[i].name))
		i++;
	if (!g_op[i].code || !(tkn->content = (void*)&g_op[i].code))
		tkn_error(INVALID_CMD, tkn, 0);
	if (g_op[i].code > MAX_COMMANDS)
		go_exit("ERROR: Please don't touch options.h file");
	test_command(tkn);
}

/*
** Если комманада, то запускаем функцию установки команды 
*/

void	this_command(t_tkn *tkn, t_tkn_sec *check_list)
{
	if (tkn->type == COMMAND)
	{
		if (!check_list->str_name)
			go_exit(NAME_MISSING);
		if (!check_list->str_comment)
			go_exit(CMNT_MISSING);
		if (!check_list->new_line)
			tkn_error(NL_MISSING, tkn, 0);
		else
			set_command(tkn, check_list, (char*)(tkn->content));
	}
}

/*
** Получаем последовательность токенов 
*/

void	tkn_sequence(t_tkn *tkn, t_tkn_sec *check_list)
{
	ft_memset(check_list, 0, sizeof(*check_list));
	check_list->new_line = true;
	while (tkn != NULL)
	{
		if (tkn->type == SEPARATOR)
		{
			if (check_list->separator)
				tkn_error(WRONG_SEPARATOR, tkn, 0);
			check_list->separator = true;
		}
		this_comment_newline(tkn, check_list);
		this_name(tkn, check_list);
		this_comment_prog(tkn, check_list);
		this_string(tkn, check_list);
		this_command(tkn, check_list);
		this_label(tkn, check_list);
		this_argument(tkn, check_list);
		tkn = tkn->next;
	}
}
