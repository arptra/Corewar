/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 19:40:57 by gemerald          #+#    #+#             */
/*   Updated: 2019/09/10 21:40:20 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned int	i;
	unsigned char	*pdest;
	unsigned char	*psrc;

	pdest = ((unsigned char *)dest);
	psrc = ((unsigned char *)src);
	i = -1;
	if (!dest && !src && (n > 0))
		return (dest);
	else
	{
		if (pdest > psrc)
		{
			while (n-- > 0)
				pdest[n] = psrc[n];
		}
		else
		{
			while (++i < n)
				pdest[i] = psrc[i];
		}
	}
	return (dest);
}
