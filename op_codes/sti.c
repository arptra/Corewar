#include "../incl/parse.h"

void	sti(t_vm *vm)
{
	uint8_t reg_num;
	int 	value;
	int 	arg_2;
	int 	arg_3;
	int 	addr;

	vm->car->move += 2; //next addr after read (instr code and type args it' have to jump 2 byte)
	reg_num = read_byte(vm, vm->car->move ) - 1; //2 is step for jump to get addr from need to read
	value = vm->car->registers[reg_num];
	vm->car->move += vm->car->args_size->arg_1;
	arg_2 = get_arg(vm, 2);
	vm->car->move += ind_move(vm->car->args_type->arg_2, vm->car->args_size->arg_2);
	arg_3 = get_arg(vm, 3);
	vm->car->move += vm->car->args_size->arg_3;
	addr = vm->car->pc + ((arg_2 + arg_3) % IDX_MOD);
	put_value(vm, addr, REG_SIZE, value);
	if (vm->d_mod == 1)
	{
		printf("P\t%d | sti r%d %d %d\n", vm->car->num, reg_num + 1, arg_2, arg_3);
		printf("\t| -> store to %d + %d = %d (with pc and mod %d)\n", arg_2, arg_3, arg_2 + arg_3, addr);
	}
	if (vm->flag_vis == 1)
		print_write_memory(vm, vm->car->p->cnum, addr, value);
}