/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tkn_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umoff <umoff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/07 13:43:24 by umoff             #+#    #+#             */
/*   Updated: 2020/07/02 14:03:34 by umoff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memlist.h"
#include "assembler.h"
#include "ft_ptintf.h"
#include "asm_word.h"

/*
** Функция печати отступов
*/

void	indent_print(char *str, u_int16_t end)
{
	while (*str && --end)
	{
		if (*str == '\t')
			write(1, "\t", 1);
		else
			write(1, " ", 1);
		str++;
	}
}

/*
** Функция получения строки из списка памяти
*/


char	*give_string_from_ml(u_int32_t row)
{
	t_ml *lst;

	lst = ml_givemem(ML_GNL_LINE);
	while (lst->next)
		lst = lst->next;
	while (--row)
		lst = lst->prev;
	return ((char *)lst->data);
}

/*
** Функция вывода токена исключения (ошибка)
*/

void	tkn_error(char *error, t_tkn *tkn, _Bool warning)
{
	char	*begin;
	char	*str;

	begin = give_string_from_ml(tkn->row);
	str = skip_delimiters(begin, SPACES);
	ft_printf("[%d:%d] %s\n\t%s\n\t", tkn->row, tkn->column, error, str);
	ft_printf("\033[0;32m%c\033[	\n", '!');
	indent_print(str, tkn->column - (str - begin));
	if (!warning)
		exit(1);
}
