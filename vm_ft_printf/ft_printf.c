/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 15:11:18 by gemerald          #+#    #+#             */
/*   Updated: 2020/01/18 20:22:32 by bgerda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		ft_printer(char *str, int *jindex, int *i, int fd)
{
	while (str[(*jindex)] != '%' && str[(*jindex)])
	{
		uputchar_fd(str[(*jindex)++], fd, 's');
		(*i)++;
	}
}

int				ft_printf(char *str, ...)
{
	int			i;
	int			jindex;
	va_list		factor;

	i = 0;
	jindex = 0;
	va_start(factor, str);
	while (str[jindex])
	{
		ft_printer(str, &jindex, &i, 1);
		if (str[jindex] == '%')
		{
			if (str[jindex + 1] == '%')
			{
				uputchar_fd(str[jindex++], 1, 's');
				i++;
			}
			else if (str[jindex + 1])
				i += voyage(&str[++jindex], &factor, &jindex, 1);
			if (str[jindex])
				jindex++;
		}
	}
	va_end(factor);
	return (i);
}

int				ft_dprintf(int fd, char *str, ...)
{
	int			i;
	int			jindex;
	va_list		factor;

	i = 0;
	jindex = 0;
	va_start(factor, str);
	while (str[jindex])
	{
		ft_printer(str, &jindex, &i, fd);
		if (str[jindex] == '%')
		{
			if (str[jindex + 1] == '%')
			{
				uputchar_fd(str[jindex++], fd, 's');
				i++;
			}
			else if (str[jindex + 1])
				i += voyage(&str[++jindex], &factor, &jindex, fd);
			if (str[jindex])
				jindex++;
		}
	}
	va_end(factor);
	return (i);
}
