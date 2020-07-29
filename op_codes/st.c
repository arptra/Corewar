#include "../incl/parse.h"

void	st(t_vm *vm)
{
	int32_t	reg_num;
	int32_t	value;
	int32_t	addr;

	vm->car->move += 2;
	reg_num = read_byte(vm, vm->car->move ) - 1;
	value = vm->car->registers[reg_num];
	vm->car->move += vm->car->args_size->arg_1;
	if (vm->car->args_type->arg_2 == T_REG)
	{
		addr = read_byte(vm, vm->car->move ) - 1;
		vm->car->registers[addr] = value;
		vm->car->move += vm->car->args_size->arg_2;
	}
	else
	{
		addr = get_value(vm, IND_SIZE);
		put_value(vm,vm->car->pc + (addr % IDX_MOD), DIR_SIZE, value);
		vm->car->move += IND_SIZE;
		if (vm->flag_vis == 1)
			print_write_memory(vm, vm->car->p->cnum, addr, value);
	}
	if (vm->d_mod == 4)
		printf("P\t%d | st r%d %d\n",vm->car->num, reg_num + 1, addr);
}