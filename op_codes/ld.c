#include "../incl/parse.h"


void 	ld(t_vm *vm)
{
	int value;
	int reg_num;

	vm->car->move += 2;
	value = get_arg(vm, 1);
	vm->car->carry = !value;
	vm->car->move += ind_move(vm->car->args_type->arg_1, vm->car->args_size->arg_1);
	reg_num = read_byte(vm, vm->car->move ) - 1;
	vm->car->registers[reg_num] = value;
	vm->car->move += vm->car->args_size->arg_2;
	// print_arena(vm->arena, 32);
}