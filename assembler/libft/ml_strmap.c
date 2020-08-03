/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umoff <umoff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 14:13:06 by umoff             #+#    #+#             */
/*   Updated: 2020/07/02 13:49:30 by umoff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ml_strmap(const char *s, char (*f)(char), u_int32_t lst_num)
{
	char	*new_str;
	char	*ptr2new;

	if (!s || !f || !(new_str = ml_strnew(ft_strlen(s), lst_num)))
		return (NULL);
	ptr2new = new_str;
	while (*s)
		*ptr2new++ = (*f)(*s++);
	return (new_str);
}
