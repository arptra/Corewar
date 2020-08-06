/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 20:18:23 by gemerald          #+#    #+#             */
/*   Updated: 2019/09/08 14:57:32 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *arr, int ch)
{
	int		index;
	char	cch;

	cch = (char)ch;
	index = 0;
	while (arr[index] != '\0')
	{
		if (arr[index] == cch)
			return (&(((char *)arr)[index]));
		index++;
	}
	if (cch == '\0')
		return (&(((char *)arr)[index]));
	return (NULL);
}
