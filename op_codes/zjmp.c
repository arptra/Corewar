#include "../incl/parse.h"

void	zjmp(t_vm *vm)
{
	int addr;

	vm->car->move += 1;
	addr = get_arg(vm, 1);
	vm->car->move += vm->car->args_size->arg_1;
	if (vm->car->carry)
	{
		vm->car->pc = get_addr(vm->car->pc + (addr % IDX_MOD));
		vm->car->move = vm->car->pc;
	}
	// print_arena(vm->arena, 32);
}