/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 21:01:03 by student           #+#    #+#             */
/*   Updated: 2020/07/30 21:01:07 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	ffork(t_vm *vm)
{
	int			addr;
	t_carriage	*car;

	vm->car->move += 1;
	addr = get_arg(vm, 1);
	vm->car->move += vm->car->a_s->arg_1;
	car = copy_carriage(vm->car, addr % IDX_MOD);
	car->num = vm->car_count + 1;
	vm->car_count++;
	add_car(&(vm->head), car);
	vm->cars_num++;
	if (vm->d_mod == 4)
		ft_printf("P\t%d | fork %d (%d)\n", vm->car->num, addr, car->pc);
	if (vm->flag_vis == 1)
		print_add_carriage(vm, car->p->cnum, car);
}
