/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 19:28:29 by gemerald          #+#    #+#             */
/*   Updated: 2019/09/08 13:39:31 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t			index;
	unsigned char	ccp;
	unsigned char	*first;
	unsigned char	*second;

	ccp = (unsigned char)c;
	index = 0;
	first = ((unsigned char *)dest);
	second = ((unsigned char *)src);
	while (index < n)
	{
		first[index] = second[index];
		if (second[index] == ccp)
			return (&dest[index + 1]);
		index++;
	}
	return (NULL);
}
