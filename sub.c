#include "parse.h"

void	sub(t_vm *vm)
{
	int reg_1;
	int reg_2;
	int reg_3;
	int value;

	vm->car->move += 2;
	reg_1 = get_arg(vm, 1);
	vm->car->move += vm->car->args_size->arg_1;
	reg_2 = get_arg(vm, 2);
	vm->car->move += vm->car->args_size->arg_2;
	value = vm->car->registers[reg_1 - 1] - vm->car->registers[reg_2 - 1];
	vm->car->carry = !value;
	reg_3 = get_arg(vm, 3);
	vm->car->registers[reg_3 - 1] = value;
	vm->car->move += vm->car->args_size->arg_3;
}