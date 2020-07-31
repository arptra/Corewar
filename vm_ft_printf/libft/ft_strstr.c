/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 21:49:30 by gemerald          #+#    #+#             */
/*   Updated: 2019/09/08 15:46:01 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *arr1, const char *arr2)
{
	int index;
	int jindex;

	index = 0;
	while (arr1[index])
	{
		jindex = 0;
		if (arr1[index] == arr2[jindex])
		{
			while ((arr1[index + jindex] == arr2[jindex]) &&
					(arr2[jindex]))
				jindex++;
			if (!arr2[jindex])
				return (((char *)&arr1[index]));
		}
		index++;
	}
	if (!arr2[0])
		return (((char *)&arr1[0]));
	return (NULL);
}
