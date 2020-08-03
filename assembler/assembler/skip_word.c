/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umoff <umoff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/31 13:40:05 by umoff             #+#    #+#             */
/*   Updated: 2020/07/02 14:03:10 by umoff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm_word.h"

/*
** Функция пропуска слова
*/

char	*skip_word(char *str, char *delims)
{
	while (*str && !this_special(*str, delims))
		str++;
	return (str);
}

/*
** Функция пропуска делиметров (ограниителей)
*/

char	*skip_delimiters(char *str, char *delims)
{
	while (*str && this_special(*str, delims))
		str++;
	return (str);
}
