/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xor.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: u18188899 <u18188899@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 21:00:13 by student           #+#    #+#             */
/*   Updated: 2020/08/01 17:24:25 by u18188899        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/corewar.h"

void	xor(t_vm *vm)
{
	int value_1;
	int value_2;
	int value;
	int reg_num;

	vm->car->move += 2;
	value_1 = get_arg(vm, 1);
	vm->car->move += ind_move(vm->car->a_t->arg_1,
			vm->car->a_s->arg_1);
	value_2 = get_arg(vm, 2);
	vm->car->move += ind_move(vm->car->a_t->arg_2,
			vm->car->a_s->arg_2);
	value = value_1 ^ value_2;
	vm->car->carry = !value;
	reg_num = read_byte(vm, vm->car->move) - 1;
	vm->car->registers[reg_num] = value;
	vm->car->move += ind_move(vm->car->a_t->arg_3,
			vm->car->a_s->arg_3);
	if (vm->d_mod == 4)
		ft_printf("P %4d | xor %d %d r%d\n", vm->car->num,
				value_1, value_2, reg_num + 1);
}
