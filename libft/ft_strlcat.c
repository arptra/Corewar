/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umoff <umoff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 14:10:14 by umoff             #+#    #+#             */
/*   Updated: 2020/07/02 13:46:32 by umoff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t dst_l;
	size_t src_l;

	dst_l = 0;
	src_l = 0;
	while (*dst)
	{
		++dst_l;
		++dst;
	}
	while (src[src_l])
		++src_l;
	if (size <= dst_l)
		src_l += size;
	else
		src_l += dst_l;
	while (*src && dst_l + 1 < size)
	{
		*dst++ = *src++;
		++dst_l;
	}
	*dst = '\0';
	return (src_l);
}
