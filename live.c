#include "parse.h"

void	live(t_vm *vm)
{
	int arg_1;

	vm->carriage->move += 1; //move on 1 byte from op code to args
	arg_1 = get_arg(vm, 1);
	vm->carriage->move += vm->carriage->args_size->arg_1;
}