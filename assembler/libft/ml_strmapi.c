/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umoff <umoff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 14:12:54 by umoff             #+#    #+#             */
/*   Updated: 2020/07/02 13:49:34 by umoff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ml_strmapi(const char *s, char (*f)(unsigned int, char),
															u_int32_t lst_num)
{
	unsigned int	i;
	char			*new_str;
	char			*ptr2new;

	if (!s || !f || !(new_str = ml_strnew(ft_strlen(s), lst_num)))
		return (NULL);
	i = 0;
	ptr2new = new_str;
	while (s[i])
	{
		*ptr2new++ = (*f)(i, s[i]);
		++i;
	}
	return (new_str);
}
