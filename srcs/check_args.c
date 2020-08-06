/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 21:05:52 by student           #+#    #+#             */
/*   Updated: 2020/07/30 21:05:55 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/corewar.h"

t_args_type	*next_decode_arg(t_args_type *type, int arg)
{
	if (arg == (T_REG | T_IND))
	{
		type->arg_1 = REG_CODE;
		type->arg_3 = IND_CODE;
	}
	else if (arg == (T_DIR | T_IND))
	{
		type->arg_2 = DIR_CODE;
		type->arg_3 = IND_CODE;
	}
	else if (arg == (T_REG | T_DIR | T_IND))
	{
		type->arg_1 = REG_CODE;
		type->arg_2 = DIR_CODE;
		type->arg_3 = IND_CODE;
	}
	return (type);
}

t_args_type	*decode_arg(int arg)
{
	t_args_type *type;

	type = init_args_type();
	if (arg == T_REG)
		type->arg_1 = REG_CODE;
	else if (arg == T_DIR)
		type->arg_2 = DIR_CODE;
	else if (arg == T_IND)
		type->arg_3 = IND_CODE;
	else if (arg == (T_REG | T_DIR))
	{
		type->arg_1 = REG_CODE;
		type->arg_2 = DIR_CODE;
	}
	else
		type = next_decode_arg(type, arg);
	return (type);
}

int			check_reg(int arg, t_vm *vm, int step)
{
	int reg;

	if (arg == REG_CODE)
	{
		reg = read_byte(vm, step);
		if (1 <= reg && reg <= REG_NUMBER)
			return (1);
		return (0);
	}
	return (1);
}

int			conjunction(int vm_arg, int ref_arg, int step, t_vm *vm)
{
	t_args_type	*ref_type;
	int			flag;

	flag = 0;
	ref_type = decode_arg(ref_arg);
	if (ref_type->arg_1 != 0 && ref_type->arg_1 == vm_arg)
		flag = 1;
	if (ref_type->arg_2 != 0 && ref_type->arg_2 == vm_arg)
		flag = 1;
	if (ref_type->arg_3 != 0 && ref_type->arg_3 == vm_arg)
		flag = 1;
	free(ref_type);
	flag += check_reg(vm_arg, vm, step);
	if (flag != 2)
		return (3);
	return (1);
}

int			ind_move(int type, int size)
{
	if (type == IND_CODE)
		return (IND_SIZE);
	return (size);
}
