/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umoff <umoff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 14:11:18 by umoff             #+#    #+#             */
/*   Updated: 2020/07/02 13:48:15 by umoff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static const char	*skip_delim(const char *s, char delim, _Bool skip)
{
	if (skip)
		while (*s && *s == delim)
			++s;
	else
		while (*s && *s != delim)
			++s;
	return (s);
}

static size_t		count_words(const char *s, char delim)
{
	size_t words;

	words = 0;
	while (*s)
	{
		s = skip_delim(s, delim, 1);
		if (*s)
		{
			++words;
			s = skip_delim(s, delim, 0);
		}
	}
	return (words);
}

static char			**clear_all(char **str_arr, int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		free(str_arr[i]);
		++i;
	}
	free(str_arr);
	str_arr = NULL;
	return (str_arr);
}

char				**ft_strsplit(const char *s, char c)
{
	char		**str_arr;
	const char	*end_word;
	int			i;

	if (!s)
		return (NULL);
	if (!(str_arr = (char **)malloc(sizeof(char *) * (count_words(s, c) + 1))))
		return (NULL);
	i = 0;
	while (*s)
	{
		s = skip_delim(s, c, 1);
		if (*s)
		{
			end_word = skip_delim(s, c, 0);
			if (!(str_arr[i] = ft_strsub(s, 0, end_word - s)))
				return (clear_all(str_arr, i));
			++i;
			s = end_word;
		}
	}
	str_arr[i] = NULL;
	return (str_arr);
}
