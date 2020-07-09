#include "parse.h"

void	lld(t_vm *vm)
{
	int value;
	int reg_num;

	vm->car->move += 2;
	value = get_arg(vm, 1);
	vm->car->move += vm->car->args_size->arg_1;
	vm->car->carry = !value;
	reg_num = get_arg(vm, 2);
	vm->car->registers[reg_num - 1] = value;
}