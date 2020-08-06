/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_codes_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 21:05:17 by student           #+#    #+#             */
/*   Updated: 2020/07/30 21:05:20 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/corewar.h"

void	reset_arg(t_vm *vm)
{
	vm->car->a_s->arg_1 = 0;
	vm->car->a_s->arg_2 = 0;
	vm->car->a_s->arg_3 = 0;
	vm->car->a_t->arg_1 = 0;
	vm->car->a_t->arg_2 = 0;
	vm->car->a_t->arg_3 = 0;
}

void	check_cycle_exec(t_vm *vm, uint8_t byte, void (*f)(t_vm *))
{
	if (vm->car->cycle_to_exec == -1)
		vm->car->cycle_to_exec = get_cycle_to_exec(byte);
	if (vm->car->cycle_to_exec > 0)
		vm->car->cycle_to_exec--;
	if (vm->car->cycle_to_exec == 0)
	{
		vm->car->op_code = byte;
		if ((vm->car->a_s->arg_1 = type_exception(byte)))
			vm->car->a_t->arg_1 = DIR_CODE;
		else
		{
			vm->car->a_s->arg_1 = type_args(vm, 1, &vm->car->a_t->arg_1);
			vm->car->a_s->arg_2 = type_args(vm, 2, &vm->car->a_t->arg_2);
			vm->car->a_s->arg_3 = type_args(vm, 3, &vm->car->a_t->arg_3);
		}
		if (check_args_type(byte, vm))
			f(vm);
		else
			vm->car->move = vm->car->tmp_addr;
		vm->car->tmp_addr = 0;
		reset_arg(vm);
		vm->car->cycle_to_exec = -1;
	}
}

void	next_slct_instr(t_vm *vm, uint8_t byte)
{
	if (byte == 0x0a)
		check_cycle_exec(vm, byte, ldi);
	else if (byte == 0x0b)
		check_cycle_exec(vm, byte, sti);
	else if (byte == 0x0c)
		check_cycle_exec(vm, byte, ffork);
	else if (byte == 0x0d)
		check_cycle_exec(vm, byte, lld);
	else if (byte == 0x0e)
		check_cycle_exec(vm, byte, lldi);
	else if (byte == 0x0f)
		check_cycle_exec(vm, byte, lfork);
	else if (byte == 0x10)
		check_cycle_exec(vm, byte, aff);
	else
		vm->car->move += 1;
}

void	slct_instr(unsigned char byte, t_vm *vm)
{
	if (byte == 0x01)
		check_cycle_exec(vm, byte, live);
	else if (byte == 0x02)
		check_cycle_exec(vm, byte, ld);
	else if (byte == 0x03)
		check_cycle_exec(vm, byte, st);
	else if (byte == 0x04)
		check_cycle_exec(vm, byte, add);
	else if (byte == 0x05)
		check_cycle_exec(vm, byte, sub);
	else if (byte == 0x06)
		check_cycle_exec(vm, byte, and);
	else if (byte == 0x07)
		check_cycle_exec(vm, byte, or);
	else if (byte == 0x08)
		check_cycle_exec(vm, byte, xor);
	else if (byte == 0x09)
		check_cycle_exec(vm, byte, zjmp);
	else
		next_slct_instr(vm, byte);
}
