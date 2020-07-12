/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umoff <umoff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 13:40:21 by umoff             #+#    #+#             */
/*   Updated: 2020/07/02 14:01:48 by umoff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "assembler.h"

/*
** Функция если попалась метка
*/

void	this_label(t_tkn *tkn, t_tkn_sec *check_list)
{
	if (tkn->type == LABEL)
	{
		if (!(check_list)->new_line)
			tkn_error(NL_MISSING, tkn, 0);
		else if (!(check_list)->str_comment)
			go_exit(CMNT_MISSING);
		else if (!check_list->str_name)
			go_exit(NAME_MISSING);
		if (!(check_list)->new_line)
			tkn_error(NL_MISSING, tkn, 0);
		else
		{
			(check_list)->arg = false;
			(check_list)->command = false;
		}
	}
}

/*
** Функция попался аргумент
*/

void	this_argument(t_tkn *tkn, t_tkn_sec *check_list)
{
	if (tkn->type == ARGUMENT || tkn->type == ARGUMENT_LABEL)
	{
		if (!(check_list)->command)
			tkn_error(CMD_MISS, tkn, 0);
		if (!(check_list)->arg && (check_list)->separator)
			tkn_error(EXTR_SPRTR, tkn, 0);
		if ((check_list)->arg && !(check_list)->separator)
			tkn_error(SPRTR_MISS, tkn, 0);
		if (((t_arg*)tkn->content)->type & T_REG &&
				(((t_arg*)tkn->content)->num < 0 ||
				((t_arg*)tkn->content)->num > 99))
			tkn_error(TREG_INVALID_NUM, tkn, 0);
		if (((t_arg*)tkn->content)->type & T_REG &&
					(((t_arg*)tkn->content)->num == 0 ||
					((t_arg*)tkn->content)->num > REG_NUMBER))
			tkn_error(WRNNG_TREG_INVALID_NUM, tkn, 1);
		(check_list)->new_line = false;
		(check_list)->separator = false;
		(check_list)->arg = true;
	}
}

/*
** Функция если попался комментарий программный
*/

void	this_comment_prog(t_tkn *tkn, t_tkn_sec *check_list)
{
	if (tkn->type == COMMENT_PROG)
	{
		if (((check_list)->name && !(check_list)->str_name) ||
			((check_list)->name && (check_list)->str_name &&
													!(check_list)->new_line))
			tkn_error(NAME_CMT, tkn, 0);
		if ((check_list)->comment_prog)
			tkn_error(DOUBLE_COMMENT, tkn, 0);
		else
			(check_list)->comment_prog = true;
	}
}

/*
** Функция если попалось имя
*/

void	this_name(t_tkn *tkn, t_tkn_sec *check_list)
{
	if (tkn->type == NAME)
	{
		if ((check_list->comment_prog && !check_list->str_comment) ||
			(check_list->comment_prog && check_list->str_comment &&
			!check_list->new_line) || check_list->name)
			tkn_error(DOUBLE_NAME, tkn, 0);
		else
			check_list->name = true;
	}
}

/*
** Функция если попался комментарий или \n
*/

void	this_comment_newline(t_tkn *tkn, t_tkn_sec *check_list)
{
	if (tkn->type == COMMENT)
	{
		check_list->new_line = false;
		check_list->comment = true;
	}
	else if (tkn->type == NEW_LINE)
	{
		if ((check_list)->separator)
			tkn_error(WRONG_SEPARATOR, tkn, 0);
		(check_list)->new_line = true;
		(check_list)->separator = false;
		(check_list)->arg = false;
	}
}
