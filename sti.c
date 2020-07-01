#include "parse.h"

void	sti(t_vm *vm)
{
	uint8_t reg_num;
	int 	value;
	int 	arg_2;
	int 	arg_3;
	int 	addr;

	vm->carriage->move = 2; //next addr after read (instr code and type args it' have to jump 2 byte)
	reg_num = get_arg(vm, 1); //2 is step for jump to get addr from need to read
	value = vm->carriage->registers[reg_num - 1];
	vm->carriage->move += vm->carriage->args->arg_1;
	arg_2 = get_arg(vm, 2);
	vm->carriage->move += vm->carriage->args->arg_2;
	arg_3 = get_arg(vm, 3);
	vm->carriage->move += vm->carriage->args->arg_3;
	addr = vm->carriage->pc + (arg_2 + arg_3) % IDX_MOD;
	put_value(vm, addr, DIR_SIZE, value);
}