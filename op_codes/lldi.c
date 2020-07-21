#include "../parse.h"

void	lldi(t_vm *vm)
{
	int addr_1;
	int addr_2;
	int reg_num;

	addr_1 = get_arg(vm, 1);
	vm->car->move += vm->car->args_size->arg_1;
	addr_2 = get_arg(vm, 2);
	vm->car->move += vm->car->args_size->arg_2;
	reg_num = read_byte(vm, vm->car->move ) - 1;
	vm->car->move += vm->car->args_size->arg_3;
	vm->car->move = vm->car->pc + addr_1 + addr_2;
	vm->car->registers[reg_num] = get_value(vm, DIR_SIZE);
	vm->car->move = vm->car->pc;
	vm->car->move += vm->car->args_size->arg_1;
	vm->car->move += vm->car->args_size->arg_2;
	vm->car->move += vm->car->args_size->arg_3;
}