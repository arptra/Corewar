#include "parse.h"

void	sti(t_vm *vm)
{
	uint8_t reg_num;
	int 	value;
	int 	cur_addr;

	reg_num = read_byte(vm, 2);// 2 is step for jump to get addr from need to read
	cur_addr = vm->carriage->cur_addr;
	value = vm->carriage->registers[reg_num - 1];

}