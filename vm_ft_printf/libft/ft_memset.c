/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 19:43:10 by gemerald          #+#    #+#             */
/*   Updated: 2019/09/08 22:04:04 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			index;
	unsigned char	set;
	unsigned char	*point;

	index = 0;
	set = c;
	point = ((unsigned char *)s);
	while (index < n)
		point[index++] = set;
	return (s);
}
