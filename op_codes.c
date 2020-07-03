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
	return (0xFF);
}

int type_args(t_vm *vm, int num_of_arg)
{
	uint8_t	type;
	int 	addr;

	addr = vm->carriage->pc;
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

int 	get_value(t_vm *vm, int size)// read from memory and translate to int
{
	int	sign;
	int value;
	int addr;
	int shift;
	uint8_t *arena;

	arena = vm->arena;
	value = 0;
	addr = vm->carriage->move % MEM_SIZE; // start address of argument (or current potion car.)
	sign = (arena[addr] >> 7) ? 1 : 0;
	shift = 0;
	while (size)
	{
		if (sign)
		{
			addr = (vm->carriage->move % MEM_SIZE) + size - 1;
			value = value + ((arena[addr] ^ 0xFF) << shift);
			shift = shift + 8;
		}
		else
		{
			addr = (vm->carriage->move % MEM_SIZE) + size - 1;
			value = value + (arena[addr] << shift);
			shift = shift + 8;
		}
		size--;
	}
	if (sign)
		value = ~(value);
	return (value);
}

void	put_value(t_vm *vm, int addr, int size, int value)
{
	int shift;
	uint8_t byte;
	int 	cur_addr;
	uint8_t *arena;

	shift = 0;
	arena = vm->arena;
	while (size)
	{
		cur_addr = (addr % MEM_SIZE) + size - 1;
		byte = value >> shift;
		arena[cur_addr] = byte;
		shift = shift + 8;
		size--;
	}
}

int 	arg_value(t_vm *vm, int	size)
{
	int 	value;

	value = 0;
	if (size == T_REG)
		value = read_byte(vm, vm->carriage->move);
	else if (size == T_DIR)
	{
		size = get_dir_size(vm->carriage->op_code);
		vm->carriage->args->arg_2 = size; //if size T_DIR change's, it should to save
		value = get_value(vm, size);
	}
	else if (size == T_IND)
	{
		value = get_value(vm, size); // get address from to read
		if (vm->carriage->op_code != 0x0e) //lldi
			value = value % IDX_MOD;
		vm->carriage->tmp_addr = vm->carriage->move; //save address to tmp var
		vm->carriage->move = value;
		value = get_value(vm, size);
		vm->carriage->move = vm->carriage->tmp_addr;
	}
	return (value);
}

int 	get_arg(t_vm *vm, int num_of_arg)
{
	int arg;
	int size;

	arg = 0;
	if (num_of_arg == 1)
	{
		size = vm->carriage->args->arg_1;
		arg = arg_value(vm, size);
	}
	else if (num_of_arg == 2)
	{
		size = vm->carriage->args->arg_2;
		arg = arg_value(vm, size);
	}
	else if (num_of_arg == 3)
	{
		size = vm->carriage->args->arg_3;
		arg = arg_value(vm, size);
	}
	return (arg);
}

int	slct_instr(unsigned char byte, t_vm *vm)
{
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
		vm->carriage->op_code = byte;
		vm->carriage->args->arg_1 = type_args(vm, 1);
		vm->carriage->args->arg_2 = type_args(vm, 2);
		vm->carriage->args->arg_3 = type_args(vm, 3);
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
