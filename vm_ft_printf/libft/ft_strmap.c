/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 20:40:14 by gemerald          #+#    #+#             */
/*   Updated: 2019/09/13 00:12:25 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	int		i;
	char	*str;
	size_t	len;

	i = 0;
	str = NULL;
	if ((s != NULL) && (f != NULL))
	{
		if (!(len = (ft_strlen(s) + 1)))
			return (NULL);
		if (!(str = (char *)malloc(sizeof(char) * (len))))
			return (NULL);
		while (s[i] != '\0')
		{
			str[i] = f(s[i]);
			i++;
		}
		str[i] = '\0';
	}
	return (str);
}
