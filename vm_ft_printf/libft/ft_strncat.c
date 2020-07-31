/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 20:44:10 by gemerald          #+#    #+#             */
/*   Updated: 2019/09/08 14:25:21 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dest, const char *src, size_t n)
{
	size_t index;
	size_t jindex;

	index = 0;
	while (dest[index])
		index++;
	jindex = 0;
	while (src[jindex] && (jindex < n))
	{
		dest[index++] = src[jindex++];
	}
	dest[index++] = '\0';
	return (dest);
}
