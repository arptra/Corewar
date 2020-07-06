#include "parse.h"

void	aff(t_vm *vm)
{
	int reg_num;
	int value;

	vm->carriage->move += 2;
	reg_num = get_arg(vm, 1);
	value = vm->carriage->registers[reg_num - 1];
	vm->carriage->move += vm->carriage->args_size->arg_1;
	/* not work now */
}