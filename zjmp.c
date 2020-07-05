#include "parse.h"

void	zjmp(t_vm *vm)
{
	int addr;

	vm->carriage->move += 1;
	addr = get_arg(vm, 1);
	if (vm->carriage->carry)
	{
		addr = (addr % IDX_MOD) % MEM_SIZE;
		vm->carriage->pc += addr;
		vm->carriage->move = vm->carriage->pc;
	}
	print_arena(vm->arena, 32);
}