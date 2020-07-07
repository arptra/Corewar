#include "parse.h"

void	lldi(t_vm *vm)
{
	int addr_1;
	int addr_2;
	int reg_num;

	addr_1 = get_arg(vm, 1);
	vm->carriage->move += vm->carriage->args_size->arg_1;
	addr_2 = get_arg(vm, 2);
	vm->carriage->move += vm->carriage->args_size->arg_2;
	reg_num = get_arg(vm, 3);
	vm->carriage->move += vm->carriage->args_size->arg_3;
	vm->carriage->move = vm->carriage->pc + addr_1 + addr_2;
	vm->carriage->registers[reg_num] = get_value(vm, DIR_SIZE);
	vm->carriage->move = vm->carriage->pc;
	vm->carriage->move += vm->carriage->args_size->arg_1;
	vm->carriage->move += vm->carriage->args_size->arg_2;
	vm->carriage->move += vm->carriage->args_size->arg_3;
}