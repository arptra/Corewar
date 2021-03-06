/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: u18188899 <u18188899@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 21:05:28 by student           #+#    #+#             */
/*   Updated: 2020/08/05 19:01:56 by u18188899        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/corewar.h"

void	ft_usage_corewar(void)
{
	int		fd;
	char	buf;

	fd = open("txt/usage_corewar.txt", O_RDONLY);
	if (fd == -1)
		exit(-1);
	while (read(fd, &buf, 1))
		write(1, &buf, 1);
	close(fd);
	exit(-1);
}

int		main(int argc, char **argv)
{
	t_vm *vm;

	if (argc == 1)
		ft_usage_corewar();
	vm = init_vm(argc, argv);
	if (vm->flag_vis == 0)
		players_intro(vm);
	exec(vm);
	if (vm->flag_vis == 0)
	{
		if (vm->d_mod != 0)
			ft_printf("Contestant %d, \"%s\", has won !\n",
					vm->last_live->cnum, vm->last_live->cn);
	}
	else
		print_declare_winner(vm);
	ft_free_vm(&vm);
}
