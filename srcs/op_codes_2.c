/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_codes_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 21:05:17 by student           #+#    #+#             */
/*   Updated: 2020/07/30 21:05:20 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/corewar.h"

int		get_value(t_vm *vm, int size)
{
	int		sign;
	int		value;
	int		addr;
	int		shift;
	uint8_t	*arena;

	arena = vm->arena;
	value = 0;
	addr = get_addr(vm->car->move);
	sign = (arena[addr] >> 7) ? 1 : 0;
	shift = 0;
	while (size)
	{
		addr = get_addr(vm->car->move + size - 1);
		if (sign)
			value = value + ((arena[addr] ^ 0xFF) << shift);
		else
			value = value + (arena[addr] << shift);
		shift = shift + 8;
		size--;
	}
	if (sign)
		value = ~(value);
	return (value);
}

void	put_value(t_vm *vm, int addr, int size, int value)
{
	int		shift;
	uint8_t	byte;
	int		cur_addr;
	uint8_t	*arena;

	shift = 0;
	arena = vm->arena;
	while (size)
	{
		cur_addr = get_addr(addr + size - 1);
		byte = value >> shift;
		arena[cur_addr] = byte;
		shift = shift + 8;
		size--;
	}
}

int		arg_value(t_vm *vm, int type, int size)
{
	int	value;

	value = 0;
	if (type == REG_CODE)
		value = vm->car->registers[read_byte(vm, vm->car->move) - 1];
	else if (type == DIR_CODE)
		value = get_value(vm, size);
	else if (type == IND_CODE)
	{
		value = get_value(vm, IND_SIZE);
		if (vm->car->op_code != 0x0d)
			value = value % IDX_MOD;
		vm->car->tmp_addr = vm->car->move;
		vm->car->move = vm->car->pc + value;
		value = get_value(vm, size);
		vm->car->move = vm->car->tmp_addr;
	}
	return (value);
}

int		get_arg(t_vm *vm, int num_of_arg)
{
	int		arg;
	int		size;
	uint8_t type;

	arg = 0;
	if (num_of_arg == 1)
	{
		type = vm->car->a_t->arg_1;
		size = vm->car->a_s->arg_1;
		arg = arg_value(vm, type, size);
	}
	else if (num_of_arg == 2)
	{
		type = vm->car->a_t->arg_2;
		size = vm->car->a_s->arg_2;
		arg = arg_value(vm, type, size);
	}
	else if (num_of_arg == 3)
	{
		type = vm->car->a_t->arg_3;
		size = vm->car->a_s->arg_3;
		arg = arg_value(vm, type, size);
	}
	return (arg);
}
