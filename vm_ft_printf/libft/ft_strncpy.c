/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 20:58:57 by gemerald          #+#    #+#             */
/*   Updated: 2019/09/05 21:00:00 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t index;

	index = 0;
	while ((index < n) && (src[index] != '\0'))
	{
		dest[index] = src[index];
		index++;
	}
	while (index < n)
		dest[index++] = '\0';
	return (dest);
}
