#include "../incl/parse.h"

void	lld(t_vm *vm)
{
	int value;
	int reg_num;

	vm->car->move += 2;
	value = get_arg(vm, 1);
	vm->car->move += ind_move(vm->car->args_type->arg_1, vm->car->args_size->arg_1);
	vm->car->carry = !value;
	reg_num = read_byte(vm, vm->car->move ) - 1;
	vm->car->registers[reg_num] = value;
	if (vm->d_mod == 4)
		printf("P\t%4d | lld %d r%d\n", vm->car->num, value, reg_num + 1);
}