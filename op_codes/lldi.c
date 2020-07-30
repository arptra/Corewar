/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lldi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 21:03:01 by student           #+#    #+#             */
/*   Updated: 2020/07/30 21:04:01 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/parse.h"

void	lldi(t_vm *vm)
{
	int addr_1;
	int addr_2;
	int reg_num;

	addr_1 = get_arg(vm, 1);
	vm->car->move += ind_move(vm->car->args_type->arg_1, vm->car->args_size->arg_1);
	addr_2 = get_arg(vm, 2);
	vm->car->move += vm->car->args_size->arg_2;
	reg_num = read_byte(vm, vm->car->move ) - 1;
	vm->car->move += vm->car->args_size->arg_3;
	vm->car->move = vm->car->pc + addr_1 + addr_2;
	vm->car->registers[reg_num] = get_value(vm, DIR_SIZE);
	vm->car->move = vm->car->pc;
	vm->car->move += ind_move(vm->car->args_type->arg_1, vm->car->args_size->arg_1);
	vm->car->move += vm->car->args_size->arg_2;
	vm->car->move += vm->car->args_size->arg_3;
	if (vm->d_mod == 4)
	{
		printf("P\t%4d | lldi %d %d r%d\n", vm->car->num, addr_1, addr_2, reg_num + 1);
		printf("       | -> load from %d + %d = %d (with pc %d)\n",
			   addr_1,
			   addr_2,
			   addr_1 + addr_2,
			   vm->car->pc + (addr_1 + addr_2));
	}
}
