/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 21:09:16 by gemerald          #+#    #+#             */
/*   Updated: 2019/09/14 15:08:59 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_word_len(const char *str, char obst)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (str[i] == obst)
		i++;
	while ((str[i + j] != obst) && str[i + j])
	{
		j++;
	}
	return (j);
}

static int		ft_word_count(const char *str, char obst)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] != obst)
		{
			count++;
			while ((str[i] != obst) && str[i])
				i++;
		}
		else
			i++;
	}
	return (count);
}

static void		*ft_free_tab(char **str, int y)
{
	while (--y)
		free(str[y]);
	free(str);
	return (NULL);
}

static char		**ft_spl_make(char const *str, char c)
{
	int		x;
	int		y;
	int		i;
	char	**spl;

	y = 0;
	i = 0;
	if (!(spl = (char **)malloc(sizeof(char *) *\
					(ft_word_count(str, c) + 1))))
		return (NULL);
	while (y < ft_word_count(str, c))
	{
		x = 0;
		if (!(spl[y] = (char *)malloc(sizeof(char) *\
						(ft_word_len(&str[i], c) + 1))))
			return (ft_free_tab(spl, y));
		while ((str[i] == c) && (str[i]))
			i++;
		while ((str[i] != c) && (str[i]))
			spl[y][x++] = str[i++];
		spl[y][x] = '\0';
		y++;
	}
	spl[y] = NULL;
	return (spl);
}

char			**ft_strsplit(char const *str, char c)
{
	char	**spl;

	spl = NULL;
	if (str && c)
		spl = ft_spl_make(str, c);
	return (spl);
}
