/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 21:04:40 by student           #+#    #+#             */
/*   Updated: 2020/07/30 21:04:46 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	zjmp(t_vm *vm)
{
	int addr;
	int flag;

	flag = 0;
	vm->car->move += 1;
	addr = get_arg(vm, 1);
	vm->car->move += vm->car->a_s->arg_1;
	if (vm->d_mod == 4)
		printf("P\t%d | zjmp ", vm->car->num);
	if (vm->car->carry)
	{
		vm->car->pc = get_addr(vm->car->pc + (addr % IDX_MOD));
		vm->car->move = vm->car->pc;
		if (vm->flag_vis == 1)
			print_move_carriage(vm, vm->car->p->cnum, (addr % IDX_MOD));
		if (vm->d_mod == 4)
			printf("%d OK\n", (addr % IDX_MOD));
		flag = 1;
	}
	if (vm->d_mod == 4 && flag == 0)
		printf("%d FAILED\n", addr);
}
