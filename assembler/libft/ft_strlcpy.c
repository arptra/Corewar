/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umoff <umoff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 14:09:57 by umoff             #+#    #+#             */
/*   Updated: 2020/07/02 13:46:36 by umoff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	len;

	if (!src || !dst)
		return (0);
	if (!size)
		return (ft_strlen(src));
	len = 0;
	while (src[len] && len < size - 1)
	{
		dst[len] = src[len];
		len++;
	}
	dst[len] = '\0';
	return (ft_strlen(src));
}
