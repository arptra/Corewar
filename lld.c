#include "parse.h"

void	lld(t_vm *vm)
{
	int value;
	int reg_num;

	vm->carriage->move += 2;
	value = get_arg(vm, 1);
	vm->carriage->move += vm->carriage->args_size->arg_1;
	vm->carriage->carry = !value;
	reg_num = get_arg(vm, 2);
	vm->carriage->registers[reg_num - 1] = value;
}