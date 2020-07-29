#include "../incl/parse.h"

void	aff(t_vm *vm)
{
	int reg_num;
	int value;

	vm->car->move += 2;
	reg_num = read_byte(vm, vm->car->move ) - 1;
	value = vm->car->registers[reg_num];
	vm->car->move += 1;
	if (vm->aff == 1)
		printf("Aff: %c\n", (char)value);
}