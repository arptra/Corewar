/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 20:45:49 by gemerald          #+#    #+#             */
/*   Updated: 2019/09/08 16:10:51 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t index;

	index = 0;
	if (n == 0)
		return (0);
	while ((str1[index] == str2[index]) && (index < n))
	{
		if (!str1[index])
			return (0);
		index++;
	}
	if (index == n)
		index--;
	return ((unsigned char)str1[index] - (unsigned char)str2[index]);
}
