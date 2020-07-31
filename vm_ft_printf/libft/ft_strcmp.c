/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 20:21:24 by gemerald          #+#    #+#             */
/*   Updated: 2019/09/08 15:53:05 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strcmp(const char *str1, const char *str2)
{
	int index;

	index = 0;
	while (str1[index] == str2[index])
	{
		if (str1[index] == '\0')
			return (0);
		index++;
	}
	return ((unsigned char)str1[index] - (unsigned char)str2[index]);
}
