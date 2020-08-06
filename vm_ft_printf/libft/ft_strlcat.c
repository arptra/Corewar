/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 20:35:58 by gemerald          #+#    #+#             */
/*   Updated: 2019/09/10 23:56:23 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t n)
{
	size_t index;
	size_t jindex;

	index = 0;
	while (dest[index] && (index < n))
		index++;
	jindex = index;
	while (((index + 1) < n) && (src[index - jindex]) != '\0')
	{
		dest[index] = src[index - jindex];
		index++;
	}
	if (jindex < n)
		dest[index] = '\0';
	return (jindex + ft_strlen(src));
}
