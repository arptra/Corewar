/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 20:55:52 by student           #+#    #+#             */
/*   Updated: 2020/07/30 20:55:55 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	ld(t_vm *vm)
{
	int	value;
	int	reg_num;

	vm->car->move += 2;
	value = get_arg(vm, 1);
	vm->car->carry = !value;
	vm->car->move += ind_move(vm->car->a_t->arg_1,
			vm->car->a_s->arg_1);
	reg_num = read_byte(vm, vm->car->move) - 1;
	vm->car->registers[reg_num] = value;
	vm->car->move += vm->car->a_s->arg_2;
	if (vm->d_mod == 4)
		ft_printf("P\t%d | ld %d r%d\n", vm->car->num, value, reg_num + 1);
}
