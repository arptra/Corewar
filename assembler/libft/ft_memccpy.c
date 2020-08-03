/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umoff <umoff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 14:05:40 by umoff             #+#    #+#             */
/*   Updated: 2020/07/02 13:41:40 by umoff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char		*to;
	const unsigned char	*from;

	to = (unsigned char *)dst;
	from = (unsigned char *)src;
	while (n > 0 && *from != (unsigned char)c)
	{
		*to++ = *from++;
		--n;
	}
	if (n > 0)
	{
		*to++ = *from++;
		return ((void *)to);
	}
	return (NULL);
}
