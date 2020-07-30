#include "../incl/parse.h"

void	zjmp(t_vm *vm)
{
	int addr;
	int flag;

	flag = 0;
	vm->car->move += 1;
	addr = get_arg(vm, 1);
	vm->car->move += vm->car->args_size->arg_1;
	if (vm->d_mod == 4)
		printf("P\t%d | zjmp ", vm->car->num);
	if (vm->car->carry)
	{
		vm->car->pc = get_addr(vm->car->pc + (addr % IDX_MOD));
		vm->car->move = vm->car->pc;
		if (vm->flag_vis == 1)
			print_move_carriage(vm, vm->car->p->cnum, (addr % IDX_MOD));
		if (vm->d_mod == 4)
			printf("%d OK\n", (addr % IDX_MOD));
		flag = 1;
	}
	if (vm->d_mod == 4 && flag == 0)
		printf("%d FAILED\n", addr);
}