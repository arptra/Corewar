/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umoff <umoff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 13:36:41 by umoff             #+#    #+#             */
/*   Updated: 2020/07/02 14:01:05 by umoff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include "ft_ptintf.h"
#include "assembler.h"

/*
** Функция распечатки в файл
*/

void	print_to_file(char *file_name, t_tkn *tkn, t_header *header)
{
	int			fd;
	int			nulle;
	char		*name;

	nulle = 0;
	errno = 0;
	if ((name = ft_strrchr(file_name, '.')))
		*name = '\0';
	name = ml_strjoin(file_name, ".cor", ML_CHECK);
	if ((fd = open(name, O_CREAT | O_WRONLY | O_TRUNC,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)) < 0)
	{
		perror("ERROR: Cant't write in file because");
		exit(1);
	}
	ft_printf("Writing output program to %s\n", name);
	header_print(fd, header);
	write(fd, &nulle, 4);
	commands_print(fd, tkn);
	close(fd);
}

/*
** Открываем и разбиваем на токены файл
*/

void	split_file_tkns(char *file_name, t_tkn_sec *check_list,
							t_tkn **tkn)
{
	int		fd;
	t_label	*label;

	label = NULL;
	errno = 0;
	if ((fd = open(file_name, O_DIRECTORY)) >= 0)
	{
		ft_printf("ERROR: %s is a directory\n", file_name);
		exit(1);
	}
	else if ((fd = open(file_name, O_RDONLY)) < 0)
	{
		ft_printf("ERROR: file %s does not exist\n", file_name);
		exit(1);
	}
	split_in_tkns(fd, tkn, &label);
	close(fd);
	tkn_sequence(*tkn, check_list);
	replace_label(label);
}

/*
** Главная функция 
*/

int		main(int ac, char **av)
{
	t_tkn		*tkn;
	t_header	header;
	t_tkn_sec	check_list;
	int			i;

	i = 0;
	while (++i < ac)
	{
		tkn = NULL;
		split_file_tkns(av[i], &check_list, &tkn);
		make_headers(&header, tkn);
		print_to_file(av[i], tkn, &header);
		ml_free_all();
	}
	return (0);
}
