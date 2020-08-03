/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   this_digit_word.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umoff <umoff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 13:38:43 by umoff             #+#    #+#             */
/*   Updated: 2020/07/02 14:03:26 by umoff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "asm_word.h"

/*
** Функция проверки слово из цифр
*/

_Bool	this_digit_word(char *str, char *delims)
{
	if (!ft_isdigit(*str))
		return (0);
	while (*str && !this_special(*str, delims))
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}
