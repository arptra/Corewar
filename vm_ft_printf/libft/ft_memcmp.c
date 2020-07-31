/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 19:33:29 by gemerald          #+#    #+#             */
/*   Updated: 2019/09/05 19:38:07 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *arr1, const void *arr2, size_t n)
{
	size_t index;

	index = 0;
	while (index < n)
	{
		if (((unsigned char *)arr1)[index] \
				!= ((unsigned char *)arr2)[index])
		{
			return (((unsigned char *)arr1)[index] -\
					((unsigned char *)arr2)[index]);
		}
		index++;
	}
	return (0);
}
