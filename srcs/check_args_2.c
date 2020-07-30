/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 21:05:52 by student           #+#    #+#             */
/*   Updated: 2020/07/30 21:05:55 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/corewar.h"

int			type_check_aux(t_vm *vm, t_args_type *check, int move)
{
	vm->car->tmp_addr = move;
	if (check->arg_1 < 2 && check->arg_2 < 2 && check->arg_3 < 2)
	{
		free(check);
		return (1);
	}
	free(check);
	return (0);
}

int			type_check(int arg_1, int arg_2, int arg_3, t_vm *vm)
{
	t_args_type	*type;
	int			move;
	t_args_type	*check;

	type = vm->car->a_t;
	move = vm->car->move + 2;
	check = init_args_type();
	if (arg_1)
	{
		check->arg_1 = conjunction(type->arg_1, arg_1, move, vm);
		move += ind_move(type->arg_1, vm->car->a_s->arg_1);
	}
	if (arg_2)
	{
		check->arg_2 = conjunction(type->arg_2, arg_2, move, vm);
		move += ind_move(type->arg_2, vm->car->a_s->arg_2);
	}
	if (arg_3)
	{
		check->arg_3 = conjunction(type->arg_3, arg_3, move, vm);
		move += ind_move(type->arg_3, vm->car->a_s->arg_3);
	}
	return (type_check_aux(vm, check, move));
}

int			check_args_type_aux(uint8_t byte, t_vm *vm)
{
	if (byte == 0x0a)
		return (type_check(T_RDI, T_RD, T_REG, vm));
	else if (byte == 0x0b)
		return (type_check(T_REG, T_RDI, T_RD, vm));
	else if (byte == 0x0c)
		return (1);
	else if (byte == 0x0d)
		return (type_check(T_DI, T_REG, 0, vm));
	else if (byte == 0x0e)
		return (type_check(T_RDI, T_RD, T_REG, vm));
	else if (byte == 0x0f)
		return (1);
	else if (byte == 0x10)
		return (type_check(T_REG, 0, 0, vm));
	return (0);
}

int			check_args_type(uint8_t byte, t_vm *vm)
{
	if (byte == 0x01)
		return (1);
	else if (byte == 0x02)
		return (type_check(T_DI, T_REG, 0, vm));
	else if (byte == 0x03)
		return (type_check(T_REG, T_RI, 0, vm));
	else if (byte == 0x04)
		return (type_check(T_REG, T_REG, T_REG, vm));
	else if (byte == 0x05)
		return (type_check(T_REG, T_REG, T_REG, vm));
	else if (byte == 0x06)
		return (type_check(T_RDI, T_RDI, T_REG, vm));
	else if (byte == 0x07)
		return (type_check(T_RDI, T_RDI, T_REG, vm));
	else if (byte == 0x08)
		return (type_check(T_RDI, T_RDI, T_REG, vm));
	else if (byte == 0x09)
		return (1);
	else
		return (check_args_type_aux(byte, vm));
}
