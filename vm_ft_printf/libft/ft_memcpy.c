/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 19:38:17 by gemerald          #+#    #+#             */
/*   Updated: 2019/09/10 23:58:10 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *destination, const void *src, size_t n)
{
	size_t			index;
	unsigned char	*first;
	unsigned char	*second;

	first = (unsigned char *)destination;
	second = (unsigned char *)src;
	index = 0;
	if (!destination && !src && (n > 0))
		return (destination);
	else
	{
		while (index < n)
		{
			first[index] = second[index];
			index++;
		}
	}
	return (destination);
}
