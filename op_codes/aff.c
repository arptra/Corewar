#include "../parse.h"

void	aff(t_vm *vm)
{
	int reg_num;
	int value;

	vm->car->move += 2;
	reg_num = read_byte(vm, vm->car->move ) - 1;
	value = vm->car->registers[reg_num];
	vm->car->move += vm->car->args_size->arg_1;
	/* not work now */
}