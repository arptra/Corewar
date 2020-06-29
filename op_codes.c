#include "parse.h"

unsigned char	select_args(unsigned char byte, int num_of_arg)
{
	if (num_of_arg == 1)
		return (byte & 0xC0);
	else if (num_of_arg == 2)
		return (byte & 0x30);
	else if (num_of_arg == 3)
		return (byte & 0xC);
	return (0xFF);
}

int select_type(uint8_t type)
{
	if (type == REG_CODE)
		return (T_REG);
	else if (type == DIR_CODE)
		return (T_DIR);
	else if (type == IND_CODE)
		return (T_IND);
}

int type_args(t_vm *vm, int num_of_arg)
{
	uint8_t	type;
	int 	addr;

	addr = vm->carriage->cur_addr;
	type = vm->arena[addr + 1];
	if (num_of_arg == 1)
	{
		type = select_args(type, 1);
		type = select_type(type >> 6);
	}
	else if (num_of_arg == 2)
	{
		type = select_args(type, 2);
		type = select_type(type >> 4);
	}
	else if (num_of_arg == 3)
	{
		type = select_args(type, 3);
		type = select_type(type >> 2);
	}
	return (type);
}

int	slct_instr(unsigned char byte, t_vm *vm)
{
	unsigned char	code_type_args;
	uint8_t			arg_1;
	uint16_t		arg_2;
	uint16_t		arg_3;
	int 			flag;

	flag = 0;
	if (byte == 0x01)
	{
		printf("hello from live\n");
	}
	else if (byte == 0x02)
	{
		printf("hello from ld\n");
	}
	else if (byte == 0x03)
	{
		printf("hello from st\n");
	}
	else if (byte == 0x04)
	{
		printf("hello from add\n");
	}
	else if (byte == 0x05)
	{
		printf("hello from sub\n");
	}
	else if (byte == 0x06)
	{
		printf("hello from and\n");
	}
	else if (byte == 0x07)
	{
		printf("hello from or\n");
	}
	else if (byte == 0x08)
	{
		printf("hello from xor\n");
	}
	else if (byte == 0x09)
	{
		printf("hello from zjmp\n");
	}
	else if (byte == 0x0a)
	{
		printf("hello from ldi\n");
	}
	else if (byte == 0x0b)
	{
		sti(vm);
		printf("hello from sti\n");
	}
	else if (byte == 0x0c)
	{
		printf("hello from fork\n");
	}
	else if (byte == 0x0d)
	{
		printf("hello from lld\n");
	}
	else if (byte == 0x0e)
	{
		printf("hello from lldi\n");
	}
	else if (byte == 0x0f)
	{
		printf("hello from lfork\n");
	}
	else if (byte == 0x10)
	{
		printf("hello from aff\n");
	}
	else
		flag = -1;
	return (flag);
}
