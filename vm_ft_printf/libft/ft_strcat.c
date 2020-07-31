/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 20:14:12 by gemerald          #+#    #+#             */
/*   Updated: 2019/09/05 20:17:53 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *dest, const char *src)
{
	int index;
	int jindex;

	index = ft_strlen(dest);
	jindex = 0;
	while (src[jindex] != '\0')
	{
		dest[index++] = src[jindex++];
	}
	dest[index] = '\0';
	return (dest);
}
