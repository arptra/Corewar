#include "../parse.h"

void	add(t_vm *vm)
{
	int reg_1;
	int reg_2;
	int reg_3;
	int value;

	vm->car->move += 2;
	reg_1 = read_byte(vm, vm->car->move ) - 1;
	vm->car->move += vm->car->args_size->arg_1;
	reg_2 = read_byte(vm, vm->car->move ) - 1;
	vm->car->move += vm->car->args_size->arg_2;
	value = vm->car->registers[reg_1] + vm->car->registers[reg_2];
	vm->car->carry = !value;
	reg_3 = read_byte(vm, vm->car->move ) - 1;
	vm->car->registers[reg_3] = value;
	vm->car->move += vm->car->args_size->arg_3;
}