/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lldi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: u18188899 <u18188899@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 21:03:01 by student           #+#    #+#             */
/*   Updated: 2020/08/01 17:24:25 by u18188899        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/corewar.h"

void	print_deb_lldi(t_vm *vm, int addr_1, int addr_2, int reg_num)
{
	ft_printf("P\t%4d | lldi %d %d r%d\n",
			vm->car->num, addr_1, addr_2, reg_num + 1);
	ft_printf("       | -> load from %d + %d = %d (with pc %d)\n",
			addr_1,
			addr_2,
			addr_1 + addr_2,
			vm->car->pc + (addr_1 + addr_2));
}

void	lldi(t_vm *vm)
{
	int addr_1;
	int addr_2;
	int reg_num;

	addr_1 = get_arg(vm, 1);
	vm->car->move += ind_move(vm->car->a_t->arg_1,
			vm->car->a_s->arg_1);
	addr_2 = get_arg(vm, 2);
	vm->car->move += vm->car->a_s->arg_2;
	reg_num = read_byte(vm, vm->car->move) - 1;
	vm->car->move += vm->car->a_s->arg_3;
	vm->car->move = vm->car->pc + addr_1 + addr_2;
	vm->car->registers[reg_num] = get_value(vm, DIR_SIZE);
	vm->car->move = vm->car->pc;
	vm->car->move += ind_move(vm->car->a_t->arg_1,
			vm->car->a_s->arg_1);
	vm->car->move += vm->car->a_s->arg_2;
	vm->car->move += vm->car->a_s->arg_3;
	if (vm->d_mod == 4)
		print_deb_lldi(vm, addr_1, addr_2, reg_num);
}
