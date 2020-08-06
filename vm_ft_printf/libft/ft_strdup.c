/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 20:25:49 by gemerald          #+#    #+#             */
/*   Updated: 2019/09/13 00:20:23 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	int		index;
	char	*dup;
	size_t	len;

	index = 0;
	if (!(len = ft_strlen(str) + 1))
		return (NULL);
	if (!(dup = (char *)malloc(sizeof(char) * (len))))
		return (NULL);
	while (str[index] != '\0')
	{
		dup[index] = str[index];
		index++;
	}
	dup[index] = '\0';
	return (dup);
}
