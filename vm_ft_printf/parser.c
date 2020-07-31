/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 18:55:11 by gemerald          #+#    #+#             */
/*   Updated: 2020/01/18 18:14:22 by bgerda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			search_others(char *str, int flags[], va_list *factor)
{
	int j;

	j = voyager_wp(str, flags, factor);
	if (str[j] == '.')
	{
		flags[6] = 1;
		j++;
		j = voyager_wp(&str[j], flags, factor) + j;
	}
	j = voyager_size(&str[j], flags) + j;
	return (j);
}

int			search_flags(char *str, int flags[])
{
	int i;

	i = 0;
	while (str[i] &&
			((str[i] == ' ') || (str[i] == '+') || (str[i] == '-') ||
			(str[i] == '0') || (str[i] == '#')))
	{
		if (str[i] == '-')
			flags[0] = (int)str[i++];
		if (str[i] == '+')
			flags[1] = (int)str[i++];
		if (str[i] == ' ')
			flags[2] = (int)str[i++];
		if (str[i] == '#')
			flags[3] = (int)str[i++];
		if (str[i] == '0')
			flags[4] = (int)str[i++];
	}
	return (i);
}

int			searcher(int flags[], char *str, char *sp, va_list *factor)
{
	int		i;
	int		j;
	char	*stop;

	i = 0;
	j = 0;
	stop = "diouxXfFeEgGcspr";
	i = search_flags(str, flags);
	i += search_others(&str[i], flags, factor);
	while (stop[j] && str[i] != stop[j])
		j++;
	(*sp) = str[i];
	return (i);
}

int			voyage(char *str, va_list *factor, int *jindex, int fd)
{
	int		i;
	int		flags[14];
	char	sp;

	i = 0;
	while (i < 12)
	{
		flags[i] = -1;
		i++;
	}
	flags[12] = fd;
	flags[13] = 0;
	i = searcher(flags, str, &sp, factor);
	*jindex = *jindex + i;
	return (find_type(factor, sp, flags));
}
