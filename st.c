#include "parse.h"

void	st(t_vm *vm)
{
	int32_t	reg_num;
	int32_t	value;
	int32_t	addr;

	vm->car->move += 2;
	reg_num = get_arg(vm, 1);
	value = vm->car->registers[reg_num];
	vm->car->move += vm->car->args_size->arg_1;
	if (vm->car->args_type->arg_2 == T_REG)
	{
		addr = get_arg(vm, 2);
		vm->car->registers[addr - 1] = value;
		vm->car->move += vm->car->args_size->arg_2;
	}
	else
	{
		addr = get_value(vm, IND_SIZE);
		put_value(vm,vm->car->pc + (addr % IDX_MOD), DIR_SIZE, value);
		vm->car->move += IND_SIZE;
	}
}