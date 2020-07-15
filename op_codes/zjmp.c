#include "../parse.h"

void	zjmp(t_vm *vm)
{
	int addr;

	vm->car->move += 1;
	addr = get_arg(vm, 1);
	vm->car->move += vm->car->args_size->arg_1;
	if (vm->car->carry)
	{
		addr = (addr % IDX_MOD) % MEM_SIZE;
		vm->car->pc += addr;
		vm->car->move = vm->car->pc;
	}
	// print_arena(vm->arena, 32);
}