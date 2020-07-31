/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 17:36:57 by gemerald          #+#    #+#             */
/*   Updated: 2020/01/18 18:17:23 by bgerda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long long int			signed_arg(va_list *factor, int flags[])
{
	if (flags[8] == 4)
		return ((short int)va_arg((*factor), int));
	else if (flags[8] == 44)
		return ((char)va_arg((*factor), int));
	else if (flags[8] == 1)
		return (va_arg((*factor), long int));
	else if (flags[8] == 11)
		return (va_arg((*factor), long long int));
	else
		return (va_arg((*factor), int));
}

unsigned long long int	unsigned_arg(va_list *factor, int flags[])
{
	if (flags[8] == 4)
		return ((unsigned short int)va_arg((*factor), unsigned int));
	else if (flags[8] == 44)
		return ((unsigned char)va_arg((*factor), unsigned int));
	else if (flags[8] == 1)
		return (va_arg((*factor), unsigned long int));
	else if (flags[8] == 11)
		return (va_arg((*factor), unsigned long long int));
	else if (flags[9] == 'p')
		return ((unsigned long long int)va_arg((*factor), void *));
	else
		return (va_arg((*factor), unsigned int));
}

int						print_char(va_list *factor, char sp, int flags[])
{
	int		i;
	char	c;

	i = 0;
	c = (char)va_arg((*factor), int);
	if (sp && flags[5] < 0)
	{
		uputchar_fd(c, flags[12], 0);
		i++;
	}
	else if (flags[0] >= 0)
	{
		uputchar_fd(c, flags[12], 0);
		while (++i < flags[5])
			uputchar_fd(' ', flags[12], 0);
	}
	else
	{
		while (++i < flags[5])
			uputchar_fd(' ', flags[12], 0);
		uputchar_fd(c, flags[12], 0);
	}
	return (i);
}
