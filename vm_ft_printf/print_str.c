/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 20:46:22 by gemerald          #+#    #+#             */
/*   Updated: 2020/01/18 20:23:58 by bgerda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	str_wide(int w, int flags[], int *j)
{
	if (flags[5] > w)
	{
		w = flags[5] - w;
		while (w-- && w >= 0)
		{
			uputchar_fd(' ', flags[12], flags[13]);
			(*j)++;
		}
	}
}

void	str_put(char *str, int flags[], int *i)
{
	if (flags[7] < 0)
	{
		while (str[(*i)])
			uputchar_fd(str[(*i)++], flags[12], flags[13]);
	}
	else if (flags[7] >= 0)
	{
		while (*i < flags[7] && str[(*i)])
			uputchar_fd(str[(*i)++], flags[12], flags[13]);
	}
	if (str[(*i)] == 0 && flags[13])
		ft_putstr(to_utf8(0x2400));
}

int		print_str(va_list *factor, char sp, int flags[])
{
	int		i;
	int		j;
	int		w;
	char	*str;

	i = 0;
	j = 0;
	if (sp == 'r')
		flags[13] = 1;
	str = va_arg((*factor), char *);
	if (str)
		w = ft_strlen(str);
	else
		w = 6;
	if (flags[7] < w && flags[7] >= 0 && sp)
		w = flags[7];
	if (flags[0] < 0)
		str_wide(w, flags, &j);
	if (!str)
		str_put("(null)", flags, &i);
	else
		str_put(str, flags, &i);
	if (flags[0] >= 0)
		str_wide(w, flags, &j);
	return (i + j);
}
