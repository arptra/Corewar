/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 20:32:46 by gemerald          #+#    #+#             */
/*   Updated: 2019/09/13 00:19:59 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*join;
	size_t	len;

	i = 0;
	j = 0;
	join = NULL;
	if (s1 && s2)
	{
		if (!(len = (ft_strlen(s1) + ft_strlen(s2)) + 1))
			return (NULL);
		if (!(join = (char *)malloc(sizeof(char) * (len))))
			return (NULL);
		while (s1[i] != '\0')
			join[j++] = s1[i++];
		i = 0;
		while (s2[i] != '\0')
			join[j++] = s2[i++];
		join[j] = '\0';
	}
	return (join);
}
