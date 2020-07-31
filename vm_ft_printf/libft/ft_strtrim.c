/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 21:55:24 by gemerald          #+#    #+#             */
/*   Updated: 2019/09/13 00:18:11 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		tr_start(const char *s)
{
	int i;

	i = 0;
	while (((s[i] == ' ') || (s[i] == '\t') || (s[i] == '\n')) &&
		s[i])
		i++;
	return (i);
}

static int		tr_end(const char *s)
{
	int len;

	len = ft_strlen(s) - 1;
	while (((s[len] == ' ') || (s[len] == '\t') ||
				(s[len] == '\n')) && (len >= 0))
		len--;
	return (len);
}

static char		*ft_strtrim_make(char const *s)
{
	int		i;
	int		j;
	int		len;
	char	*str;

	j = 0;
	i = tr_start(s);
	len = tr_end(s);
	if (len < 0)
	{
		if (!(str = (char *)malloc(sizeof(char) * (1))))
			return (NULL);
	}
	else
	{
		if (!(str = (char *)malloc(sizeof(char) * (len - i) + 2)))
			return (NULL);
		while (i <= len)
		{
			str[j++] = s[i++];
		}
	}
	str[j] = '\0';
	return (str);
}

char			*ft_strtrim(char const *s)
{
	char	*str;

	str = NULL;
	if (s)
		str = ft_strtrim_make(s);
	return (str);
}
