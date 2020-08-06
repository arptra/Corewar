/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 19:31:47 by gemerald          #+#    #+#             */
/*   Updated: 2019/09/10 22:59:08 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memchr(const void *arr, int c, size_t n)
{
	size_t index;

	index = 0;
	while (index < n)
	{
		if (((unsigned const char *)arr)[index] ==\
				(unsigned char)c)
			return (&((void *)arr)[index]);
		index++;
	}
	return (NULL);
}
