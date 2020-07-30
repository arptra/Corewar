/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 20:55:07 by student           #+#    #+#             */
/*   Updated: 2020/07/30 20:55:20 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	add(t_vm *vm)
{
	int reg_1;
	int reg_2;
	int reg_3;
	int value;

	vm->car->move += 2;
	reg_1 = read_byte(vm, vm->car->move) - 1;
	vm->car->move += vm->car->a_s->arg_1;
	reg_2 = read_byte(vm, vm->car->move) - 1;
	vm->car->move += vm->car->a_s->arg_2;
	value = vm->car->registers[reg_1] + vm->car->registers[reg_2];
	vm->car->carry = !value;
	reg_3 = read_byte(vm, vm->car->move) - 1;
	vm->car->registers[reg_3] = value;
	vm->car->move += vm->car->a_s->arg_3;
	if (vm->d_mod == 4)
		printf("P\t%d | add r%d r%d r%d\n", vm->car->num,
				reg_1 + 1, reg_2 + 1, reg_3 + 1);
}
