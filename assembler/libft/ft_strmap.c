/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umoff <umoff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 14:10:25 by umoff             #+#    #+#             */
/*   Updated: 2020/07/02 13:46:43 by umoff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(const char *s, char (*f)(char))
{
	char	*new_str;
	char	*ptr2new;

	if (!s || !f || !(new_str = ft_strnew(ft_strlen(s))))
		return (NULL);
	ptr2new = new_str;
	while (*s)
		*ptr2new++ = (*f)(*s++);
	return (new_str);
}
