#include "parse.h"

void	or(t_vm *vm)
{
	int value_1;
	int value_2;
	int reg_num;
	int value;

	vm->car->move += 2;
	value_1 = get_arg(vm, 1);
	vm->car->move += vm->car->args_size->arg_1;
	value_2 = get_arg(vm, 2);
	vm->car->move += vm->car->args_size->arg_2;
	value = value_1 | value_2;
	vm->car->carry = !value;
	reg_num = get_arg(vm, 3);
	vm->car->registers[reg_num - 1] = value;
	vm->car->move += vm->car->args_size->arg_3;
}