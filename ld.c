#include "parse.h"


void 	ld(t_vm *vm)
{
	int value;
	int reg_num;

	vm->carriage->move += 2;
	value = get_arg(vm, 1);
	vm->carriage->carry = !value;
	vm->carriage->move += vm->carriage->args_size->arg_1;
	reg_num = get_arg(vm, 2);
	vm->carriage->registers[reg_num - 1] = value;
	vm->carriage->move += vm->carriage->args_size->arg_2;
	// print_arena(vm->arena, 32);
}