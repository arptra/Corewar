/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umoff <umoff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 14:11:07 by umoff             #+#    #+#             */
/*   Updated: 2020/07/02 13:47:25 by umoff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	const char	*haystack;
	const char	*needle;
	size_t		curr_len;

	if (!(*to_find))
		return ((char*)str);
	while (*str && len > 0)
	{
		if (*str == *to_find)
		{
			haystack = (const char*)str;
			needle = (const char*)to_find;
			curr_len = len;
			while (curr_len > 0 && *haystack++ == *needle++ && *needle)
				--curr_len;
			if (!(*needle) && (*(haystack - 1) == *(needle - 1)))
				return ((char *)str);
		}
		++str;
		--len;
	}
	return (NULL);
}
