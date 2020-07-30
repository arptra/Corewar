/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_codes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 21:05:17 by student           #+#    #+#             */
/*   Updated: 2020/07/30 21:05:20 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/corewar.h"

uint8_t	select_args(unsigned char byte, int num_of_arg)
{
	if (num_of_arg == 1)
		return (byte & 0xC0);
	else if (num_of_arg == 2)
		return (byte & 0x30);
	else if (num_of_arg == 3)
		return (byte & 0xC);
	return (0xFF);
}

int		select_size(uint8_t type, uint8_t byte)
{
	if (type == REG_CODE)
		return (T_REG);
	else if (type == DIR_CODE)
		return (get_dir_size(byte));
	else if (type == IND_CODE)
		return (T_IND);
	return (T_IND);
}

uint8_t	select_type(uint8_t type)
{
	if (type == REG_CODE)
		return (REG_CODE);
	else if (type == DIR_CODE)
		return (DIR_CODE);
	else if (type == IND_CODE)
		return (IND_CODE);
	return (IND_CODE);
}

int		type_args(t_vm *vm, int num_of_arg, uint8_t *type)
{
	uint8_t	size_type;
	int		addr;

	addr = get_addr(vm->car->pc + 1);
	size_type = vm->arena[addr];
	if (num_of_arg == 1)
	{
		size_type = select_args(size_type, 1);
		*type = select_type(size_type >> 6);
		size_type = select_size(size_type >> 6, vm->car->op_code);
	}
	else if (num_of_arg == 2)
	{
		size_type = select_args(size_type, 2);
		*type = select_type(size_type >> 4);
		size_type = select_size(size_type >> 4, vm->car->op_code);
	}
	else if (num_of_arg == 3)
	{
		size_type = select_args(size_type, 3);
		*type = select_type(size_type >> 2);
		size_type = select_size(size_type >> 2, vm->car->op_code);
	}
	return (size_type);
}
