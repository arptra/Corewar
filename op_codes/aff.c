/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 21:00:43 by student           #+#    #+#             */
/*   Updated: 2020/07/30 21:00:48 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/parse.h"

void	aff(t_vm *vm)
{
	int reg_num;
	int value;

	vm->car->move += 2;
	reg_num = read_byte(vm, vm->car->move ) - 1;
	value = vm->car->registers[reg_num];
	vm->car->move += 1;
	if (vm->aff == 1)
		printf("Aff: %c\n", (char)value);
}
