/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   or.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 20:59:33 by student           #+#    #+#             */
/*   Updated: 2020/07/30 20:59:37 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	or(t_vm *vm)
{
	int value_1;
	int value_2;
	int reg_num;
	int value;

	vm->car->move += 2;
	value_1 = get_arg(vm, 1);
	vm->car->move += ind_move(vm->car->a_t->arg_1,
			vm->car->a_s->arg_1);
	value_2 = get_arg(vm, 2);
	vm->car->move += ind_move(vm->car->a_t->arg_2,
			vm->car->a_s->arg_2);
	value = value_1 | value_2;
	vm->car->carry = !value;
	reg_num = read_byte(vm, vm->car->move) - 1;
	vm->car->registers[reg_num] = value;
	vm->car->move += ind_move(vm->car->a_t->arg_3,
			vm->car->a_s->arg_3);
	if (vm->d_mod == 4)
		printf("P\t%4d | or %d %d r%d\n", vm->car->num,
				value_1, value_2, reg_num + 1);
}
