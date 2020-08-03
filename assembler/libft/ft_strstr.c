/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umoff <umoff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 14:11:24 by umoff             #+#    #+#             */
/*   Updated: 2020/07/02 13:48:19 by umoff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strstr(const char *str, const char *to_find)
{
	const char	*haystack;
	const char	*needle;

	if (!(*to_find))
		return ((char*)str);
	while (*str)
	{
		if (*str == *to_find)
		{
			haystack = (const char*)str;
			needle = (const char*)to_find;
			while (*haystack++ == *needle++ && *needle)
				;
			if (!(*needle) && (*(haystack - 1) == *(needle - 1)))
				return ((char *)str);
		}
		++str;
	}
	return (NULL);
}
