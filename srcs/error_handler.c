/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 21:05:43 by student           #+#    #+#             */
/*   Updated: 2020/07/30 21:05:45 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/corewar.h"

void				ft_error(int code, t_vm *vm)
{
	int				fd;
	char			buf;
	int				i1;

	i1 = 1;
	ft_free_vm(&vm);
	if ((fd = open("txt/errors.txt", O_RDONLY)) == -1)
		exit(-1);
	while (read(fd, &buf, 1))
	{
		if (buf == '\n' && i1 > code)
			break ;
		if (i1 == code)
			write(2, &buf, 1);
		if (buf == '\n')
			i1++;
	}
	close(fd);
	exit(code);
}
