/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tkn_strcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umoff <umoff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 13:43:11 by umoff             #+#    #+#             */
/*   Updated: 2020/07/02 14:03:44 by umoff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "asm_errors.h"
#include "assembler.h"

/*
** Функция поиска токена 
*/

t_tkn		*find_tkn(t_tkn *head, t_tkn_type type)
{
	while (head && head->type != type)
		head = head->next;
	if (!head)
	{
		ft_printf("ERROR: can't find tkn %s\n", g_type[type]);
		exit(1);
	}
	return (head);
}

/*
** Функция подсчета двойных кавычек
*/

u_int8_t	count_double_quotes(char *str)
{
	u_int8_t dq;

	dq = 0;
	while ((str = ft_strchr(str, '"')))
	{
		str++;
		dq++;
	}
	return (dq);
}

/*
** Функция подсчета длины строки токена
*/

u_int16_t	tkn_str_len(t_tkn *tkn, u_int16_t *tkn_num)
{
	int			len;
	u_int8_t	dq;

	if (tkn->type != STRING)
		tkn_error(INVALID_STR_PLACE, tkn, 0);
	len = -2;
	dq = 0;
	*tkn_num = 0;
	while (tkn && (tkn->type == STRING || tkn->type == NEW_LINE) && dq < 2)
	{
		if (tkn->type == STRING)
		{
			len += ft_strlen((char*)tkn->content);
			dq += count_double_quotes((char*)tkn->content);
			(*tkn_num)++;
		}
		tkn = tkn->next;
	}
	if (!tkn || !tkn->next || tkn->next->type == END)
		go_exit(NOCODE);
	if (len < 0)
		go_exit(INVALID_STR);
	return (len + *tkn_num - 1);
}

/*
** Функция перехода к следующей строке
*/

t_tkn		*go_next_string(t_tkn *tkn)
{
	if (!tkn->next || tkn->next->type != NEW_LINE || !tkn->next->next ||
		tkn->next->next->type != STRING)
		go_exit(INVALID_STR);
	return (tkn->next->next);
}

/*
** Функция объединения токенов 
*/

char		*tkn_strcat(char *dst, t_tkn *tkn, u_int32_t max_len)
{
	u_int16_t	len;
	u_int16_t	tkn_num;

	if (tkn->type != STRING)
		tkn_error(INVALID_STR_PLACE, tkn, 0);
	if ((len = tkn_str_len(tkn, &tkn_num)) > max_len)
		go_exit((max_len == PROG_NAME_LENGTH) ? LONG_NAME : LONG_CMNT);
	if (tkn_num == 1)
		return (ft_strncat(dst, (char*)tkn->content + 1, len));
	ft_strcat(ft_strcat(dst, (char*)tkn->content + 1), "\n");
	tkn = go_next_string(tkn);
	tkn_num -= 2;
	while (tkn_num--)
	{
		ft_strcat(ft_strcat(dst, (char*)tkn->content), "\n");
		tkn = go_next_string(tkn);
	}
	return (ft_strncat(dst, (char*)tkn->content,
										ft_strlen((char*)tkn->content) - 1));
}
