/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: u18188899 <u18188899@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 21:04:40 by student           #+#    #+#             */
/*   Updated: 2020/08/01 17:24:25 by u18188899        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/corewar.h"

void	zjmp(t_vm *vm)
{
	int addr;
	int flag;

	flag = 0;
	vm->car->move += 1;
	addr = get_arg(vm, 1);
	vm->car->move += vm->car->a_s->arg_1;
	if (vm->d_mod == 4)
		ft_printf("P\t%d | zjmp ", vm->car->num);
	if (vm->car->carry)
	{
		vm->car->pc = get_addr(vm->car->pc + (addr % IDX_MOD));
		vm->car->move = vm->car->pc;
		if (vm->flag_vis == 1)
			print_move_carriage(vm, vm->car->p->cnum, (addr % IDX_MOD));
		if (vm->d_mod == 4)
			ft_printf("%d OK\n", (addr % IDX_MOD));
		flag = 1;
	}
	if (vm->d_mod == 4 && flag == 0)
		ft_printf("%d FAILED\n", addr);
}
