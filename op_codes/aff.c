/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: u18188899 <u18188899@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 21:00:43 by student           #+#    #+#             */
/*   Updated: 2020/08/01 17:24:25 by u18188899        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/corewar.h"

void	aff(t_vm *vm)
{
	int reg_num;
	int value;

	vm->car->move += 2;
	reg_num = read_byte(vm, vm->car->move) - 1;
	value = vm->car->registers[reg_num];
	vm->car->move += 1;
	if (vm->aff == 1)
		ft_printf("Aff: %c\n", (char)value);
}
