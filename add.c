#include "parse.h"

void	add(t_vm *vm)
{
	int reg_1;
	int reg_2;
	int reg_3;
	int value;

	vm->carriage->move += 2;
	reg_1 = get_arg(vm, 1);
	vm->carriage->move += vm->carriage->args_size->arg_1;
	reg_2 = get_arg(vm, 2);
	vm->carriage->move += vm->carriage->args_size->arg_2;
	value = vm->carriage->registers[reg_1 - 1] + vm->carriage->registers[reg_2 - 1];
	vm->carriage->carry = !value;
	reg_3 = get_arg(vm, 3);
	vm->carriage->registers[reg_3] = value;
	vm->carriage->move += vm->carriage->args_size->arg_3;
}