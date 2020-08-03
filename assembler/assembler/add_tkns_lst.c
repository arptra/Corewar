/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_tkns_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umoff <umoff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 13:41:21 by umoff             #+#    #+#             */
/*   Updated: 2020/07/02 14:01:22 by umoff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"
#include "libft.h"
#include "asm_word.h"

/*
** Функция добавления аргумента
*/

t_arg		*add_arg(char *str, t_arg_type type)
{
	t_arg *new;

	new = (t_arg*)ml_malloc(sizeof(t_arg), ML_ARGUMENT);
	new->type = type;
	new->content = NULL;
	if (type & T_LAB)
		return (new);
	if (type & T_REG || type & T_DIR)
		new->num = ft_atoi(str + 1);
	else if (type & T_IND)
		new->num = ft_atoi(str);
	return (new);
}

/*
** Функция добавления метки
*/

void		add_label(char *str, t_tkn *tkn,
											t_label **tail, t_arg_type arg_type)
{
	t_label	*new;

	new = (t_label*)ml_malloc(sizeof(t_label), ML_LABEL);
	new->tkn = tkn;
	new->name = ml_strndup(str, skip_word(str, DELIMITERS) - str, ML_L_NAME);
	new->next = NULL;
	if (arg_type)
	{
		tkn->content = (void*)add_arg(NULL, arg_type);
		((t_arg*)tkn->content)->content = (void*)new;
	}
	else
		tkn->content = (void*)new;
	if (!*tail)
		new->prev = NULL;
	else
	{
		new->prev = *tail;
		(*tail)->next = new;
	}
	*tail = new;
}

/*
** Функция добавления строки
*/

char		*add_string(char *str, t_tkn *tkn)
{
	char *temp;

	tkn->type = STRING;
	temp = str + ((*str == '"') ? 1 : 0);
	if (*temp == '"')
	{
		tkn->content = (char*)ml_memalloc(sizeof(char) * 3, ML_S_CONTENT);
		ft_memset((char*)tkn->content, '"', 2);
		return (temp + 1);
	}
	while (*temp && *temp != '"')
		temp++;
	if (*temp == '"')
		temp++;
	tkn->content = (void*)ml_strndup(str, temp - str, ML_S_CONTENT);
	return (temp);
}

/*
** Функция проверки предыдущей строки
*/

u_int8_t	check_prev_str(t_tkn *tkn, u_int8_t flag)
{
	char *str;
	char *str_end;

	if (!tkn || tkn->type != NEW_LINE || !tkn->prev ||
		tkn->prev->type != STRING)
		return (flag);
	str = (char*)tkn->prev->content;
	if (tkn->prev->prev && tkn->prev->prev->type == NEW_LINE &&
		tkn->prev->prev->prev && tkn->prev->prev->prev->type == STRING)
		;
	else if (*str == '"')
		str++;
	if ((str_end = ft_strchr(str, '"')) && !*(str_end + 1))
		return (flag);
	return (NOTENDSTR);
}

/*
** Функция добавления токена
*/

t_tkn		*add_tkn(t_pc *pc, t_tkn **tkn_tail,
											t_label **label_tail, u_int8_t flag)
{
	t_tkn *new;

	new = (t_tkn*)ml_malloc(sizeof(t_tkn), ML_TOKEN);
	tkn_fill(pc->line, new, label_tail, check_prev_str(*tkn_tail, flag));
	new->row = pc->row;
	new->column = pc->column;
	new->next = NULL;
	if (!*tkn_tail)
		new->prev = NULL;
	else
	{
		new->prev = *tkn_tail;
		(*tkn_tail)->next = new;
	}
	*tkn_tail = new;
	return (new);
}
