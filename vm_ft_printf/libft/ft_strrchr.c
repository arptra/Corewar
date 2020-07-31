/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 21:07:57 by gemerald          #+#    #+#             */
/*   Updated: 2019/09/05 21:08:54 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *arr, int ch)
{
	int index;

	index = ft_strlen(arr);
	while (index > -1)
	{
		if (arr[index] == ch)
			return (&((char *)arr)[index]);
		index--;
	}
	return (NULL);
}
