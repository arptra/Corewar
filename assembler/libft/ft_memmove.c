/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umoff <umoff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 14:06:51 by umoff             #+#    #+#             */
/*   Updated: 2020/07/02 13:42:17 by umoff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*to;
	const char	*from;

	if (!dst && !src)
		return (NULL);
	to = (char *)dst;
	from = (const char *)src;
	if (from > to)
		while (len--)
			*to++ = *from++;
	else
	{
		from = from + len - 1;
		to = to + len - 1;
		while (len--)
			*to-- = *from--;
	}
	return (dst);
}
