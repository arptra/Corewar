#include "../incl/parse.h"

void	and(t_vm *vm)
{
	int	value_1;
	int	value_2;
	int	value;
	int	reg_num;

	vm->car->move += 2;
	value_1 = get_arg(vm, 1);
	vm->car->move += ind_move(vm->car->args_type->arg_1, vm->car->args_size->arg_1);
	value_2 = get_arg(vm, 2);
	vm->car->move += ind_move(vm->car->args_type->arg_2, vm->car->args_size->arg_2);
	value = value_1 & value_2;
	vm->car->carry = !value;
	reg_num = read_byte(vm, vm->car->move ) - 1;
	vm->car->registers[reg_num] = value;
	vm->car->move += ind_move(vm->car->args_type->arg_3, vm->car->args_size->arg_3);
	if (vm->d_mod == 4)
		printf("P\t%4d | and %d %d r%d\n", vm->car->num, value_1, value_2, reg_num + 1);

}