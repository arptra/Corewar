#include "parse.h"

unsigned char	args_type(unsigned char byte, int num_of_arg)
{
	if (num_of_arg == 1)
		return (byte & 0xC0);
	else if (num_of_arg == 2)
		return (byte & 0x30);
	else if (num_of_arg == 3)
		return (byte & 0xC);
	return (0xFF);
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
		printf("hello from and");
	}
	else if (byte == 0x07)
	{
		printf("hello from or");
	}
	else if (byte == 0x08)
	{
		printf("hello from xor");
	}
	else if (byte == 0x09)
	{
		printf("hello from zjmp");
	}
	else if (byte == 0x0a)
	{
		printf("hello from ldi");
	}
	else if (byte == 0x0b)
	{
		printf("hello from sti");
	}
	else if (byte == 0x0c)
	{
		printf("hello from fork");
	}
	else if (byte == 0x0d)
	{
		printf("hello from lld");
	}
	else if (byte == 0x0e)
	{
		printf("hello from lldi");
	}
	else if (byte == 0x0f)
	{
		printf("hello from lfork");
	}
	else if (byte == 0x10)
	{
		printf("hello from aff");
	}
	else
		flag = -1;
	return (flag);
}
