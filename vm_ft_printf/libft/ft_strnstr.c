/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 21:05:29 by gemerald          #+#    #+#             */
/*   Updated: 2019/09/10 23:10:47 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *arr1, const char *arr2, size_t n)
{
	size_t index;
	size_t jindex;

	index = 0;
	if (arr2[0] == '\0')
		return (((char *)&arr1[index]));
	while ((index < n) && (arr1[index]))
	{
		jindex = 0;
		if (arr1[index] == arr2[jindex])
		{
			while ((arr1[index + jindex] == arr2[jindex]) &&
					((index + jindex) < n) && (arr2[jindex]))
				jindex++;
			if (!arr2[jindex])
				return (((char *)&arr1[index]));
		}
		index++;
	}
	return (NULL);
}
