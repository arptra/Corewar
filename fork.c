#include "parse.h"

void ffork(t_vm *vm)
{
	int		addr;
	t_carriage	*car;

	vm->car->move += 1;
	addr = get_arg(vm, 1);
	car = copy_carriage(vm->car, addr % IDX_MOD);
	add_car(&(vm->car), car);
	vm->cars_num++;
}