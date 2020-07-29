#include "../incl/parse.h"

void ffork(t_vm *vm)
{
	int		addr;
	t_carriage	*car;

	vm->car->move += 1;
	addr = get_arg(vm, 1);
	vm->car->move += vm->car->args_size->arg_1;
	car = copy_carriage(vm->car, addr % IDX_MOD);
	car->num = vm->cars_num + 1;
	add_car(&(vm->head), car);
	vm->cars_num++;
	if (vm->d_mod == 4)
		printf("P\t%d | fork %d (%d)\n", vm->car->num, addr, car->pc);
	if (vm->flag_vis == 1)
		print_add_carriage(vm, car->p->cnum, car);
}