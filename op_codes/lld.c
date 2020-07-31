/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lld.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 20:58:10 by student           #+#    #+#             */
/*   Updated: 2020/07/30 20:58:40 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	lld(t_vm *vm)
{
	int value;
	int reg_num;

	vm->car->move += 2;
	value = get_arg(vm, 1);
	vm->car->move += ind_move(vm->car->a_t->arg_1,
			vm->car->a_s->arg_1);
	vm->car->carry = !value;
	reg_num = read_byte(vm, vm->car->move) - 1;
	vm->car->registers[reg_num] = value;
	if (vm->d_mod == 4)
		ft_printf("P\t%4d | lld %d r%d\n",
				vm->car->num, value, reg_num + 1);
}
