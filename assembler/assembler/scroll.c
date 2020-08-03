/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scroll.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umoff <umoff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/31 13:43:05 by umoff             #+#    #+#             */
/*   Updated: 2020/07/02 14:02:58 by umoff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"
#include "asm_word.h"
#include "libft.h"

/*
** Функция перематывания на n
*/

void		scroll_n(t_pc *pc, u_int16_t n)
{
	pc->line += n;
	pc->column += n;
}

/*
** Функция перематывания строки
*/

u_int8_t	string_scroll(t_pc *pc)
{
	char *str_end;

	if (*pc->line == '"')
		scroll_n(pc, 1);
	if (!(str_end = ft_strchr(pc->line, '"')))
		return (TKNZE_BREAK);
	scroll_n(pc, str_end - pc->line + 1);
	scroll_n(pc, skip_delimiters(pc->line, SPACES) - pc->line);
	return (TKNZE_CONT);
}

/*
** Функция перематывания аргумента
*/

void		argument_scroll(t_pc *pc, t_tkn *tkn)
{
	t_arg	*arg;
	char	*temp;

	arg = (t_arg*)tkn->content;
	if (arg->type & T_REG || arg->type & T_DIR)
		scroll_n(pc, 1);
	if (tkn->type == ARGUMENT_LABEL)
		scroll_n(pc, 1);
	if (*pc->line == '-')
		scroll_n(pc, 1);
	temp = skip_word(pc->line, DELIMITERS);
	scroll_n(pc, temp - pc->line);
}

/*
** Функция перематывания команды
*/

void		command_scroll(t_pc *pc, t_tkn *tkn)
{
	if (!tkn->content || !*(char*)tkn->content ||
							this_special(*(char*)tkn->content, DELIMITERS))
		tkn_error(INVALID_CMD, tkn, 0);
	scroll_n(pc, skip_word(pc->line, DELIMITERS) - pc->line);
}

/*
** Функция перематывания токена
*/

u_int8_t	tkn_scroll(t_pc *pc, t_tkn *tkn)
{
	if (tkn->type == COMMENT)
		return (TKNZE_BREAK);
	else if (tkn->type == ARGUMENT || tkn->type == ARGUMENT_LABEL)
		argument_scroll(pc, tkn);
	else if (tkn->type == COMMAND)
		command_scroll(pc, tkn);
	else if (tkn->type == SEPARATOR)
		scroll_n(pc, 1);
	else if (tkn->type == LABEL)
		scroll_n(pc, skip_word(pc->line, DELIMITERS) - pc->line + 1);
	else if (tkn->type == STRING)
		return (string_scroll(pc));
	else if (tkn->type == NAME)
		scroll_n(pc, ft_strlen(NAME_CMD_STRING));
	else if (tkn->type == COMMENT_PROG)
		scroll_n(pc, ft_strlen(COMMENT_CMD_STRING));
	scroll_n(pc, skip_delimiters(pc->line, SPACES) - pc->line);
	return (TKNZE_CONT);
}
