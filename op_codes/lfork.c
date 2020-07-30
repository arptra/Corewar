/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lfork.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 20:56:49 by student           #+#    #+#             */
/*   Updated: 2020/07/30 20:56:52 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/parse.h"

void	lfork(t_vm *vm)
{
	int			addr;
	t_carriage	*car;

	vm->car->move += 1;
	addr = get_arg(vm, 1);
	vm->car->move += vm->car->a_s->arg_1;
	car = copy_carriage(vm->car, addr);
	car->num = vm->car_count + 1;
	vm->car_count++;
	add_car(&(vm->head), car);
	vm->cars_num++;
	if (vm->d_mod == 4)
		printf("P\t%4d | lfork %d (%d)\n", vm->car->num, addr, vm->car->pc);
	if (vm->flag_vis == 1)
		print_add_carriage(vm, car->p->cnum, car);
}
