/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equals.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umoff <umoff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 13:40:14 by umoff             #+#    #+#             */
/*   Updated: 2020/07/02 14:02:01 by umoff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Функция сравнения слов
*/

int		equals(char *ethalon, char *str, char *delims)
{
	while (*ethalon && *str)
	{
		if (!*ethalon && *str)
		{
			while (*delims)
			{
				if (*str == *delims)
					return (1);
				delims++;
			}
			return (0);
		}
		if (*ethalon != *str)
			return (0);
		ethalon++;
		str++;
	}
	return (1);
}
