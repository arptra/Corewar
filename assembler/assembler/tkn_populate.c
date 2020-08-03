/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tkn_populate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umoff <umoff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 13:43:32 by umoff             #+#    #+#             */
/*   Updated: 2020/07/02 14:03:38 by umoff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "assembler.h"
#include "asm_word.h"

/*
** Функция проверки на аргумент состоящего из чисел
*/

_Bool	is_numarg(char *str)
{
	if (*str == '-')
		str++;
	return (this_digit_word(str, DELIMITERS));
}

/*
** Функция распознания метки аргумента 
*/

_Bool	arg_label_recognition(char *str, t_tkn *tkn, t_label **tail)
{
	if (*str == REGISTER_CHAR && is_numarg(str + 1))
		tkn->content = (void*)add_arg(str, T_REG);
	else if (*str == DIRECT_CHAR && is_numarg(str + 1))
		tkn->content = (void*)add_arg(str, T_DIR);
	else if (is_numarg(str))
		tkn->content = (void*)add_arg(str, T_IND);
	else if ((*str == DIRECT_CHAR && *(str + 1) == LABEL_CHAR) ||
															*str == LABEL_CHAR)
	{
		if (*str == LABEL_CHAR)
			add_label(str + 1, tkn, tail, T_IND | T_LAB);
		else
			add_label(str + 2, tkn, tail, T_DIR | T_LAB);
		tkn->type = ARGUMENT_LABEL;
		return (1);
	}
	else
		return (0);
	tkn->type = ARGUMENT;
	return (1);
}

/*
** Функция распознания метки
*/

_Bool	label_recognition(char *str, t_tkn *tkn, t_label **tail)
{
	char *temp;

	temp = str;
	while (*temp && !this_special(*temp, DELIMITERS))
	{
		if (!this_special(*temp, LABEL_CHARS))
			return (0);
		temp++;
	}
	if (*temp != LABEL_CHAR)
		return (0);
	add_label(str, tkn, tail, 0);
	return (1);
}

/*
** Функция заполнения токена
*/

void	tkn_fill(char *str, t_tkn *tkn, t_label **tail, u_int8_t flag)
{
	if (flag == ENDFILE)
		tkn->type = END;
	else if (*str == '"' || flag == NOTENDSTR)
		add_string(str, tkn);
	else if (!*str || flag == ENDLINE)
		tkn->type = NEW_LINE;
	else if (*str == SEPARATOR_CHAR)
		tkn->type = SEPARATOR;
	else if (*str == COMMENT_CHAR || *str == ALT_COMMENT_CHAR)
		tkn->type = COMMENT;
	else if (*str == '.' && equals(NAME_CMD_STRING, str, DELIMITERS))
		tkn->type = NAME;
	else if (*str == '.' && equals(COMMENT_CMD_STRING, str, DELIMITERS))
		tkn->type = COMMENT_PROG;
	else if (arg_label_recognition(str, tkn, tail))
		;
	else if (label_recognition(str, tkn, tail))
		tkn->type = LABEL;
	else
	{
		tkn->type = COMMAND;
		tkn->content = (void*)ml_strndup(str,
				skip_word(str, DELIMITERS) - str, ML_CMD_NAME);
	}
}
