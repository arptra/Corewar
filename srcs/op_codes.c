#include "../incl/parse.h"

uint8_t	select_args(unsigned char byte, int num_of_arg)
{
	if (num_of_arg == 1)
		return (byte & 0xC0);
	else if (num_of_arg == 2)
		return (byte & 0x30);
	else if (num_of_arg == 3)
		return (byte & 0xC);
	return (0xFF);
}

int		select_size(uint8_t type, uint8_t byte)
{
	if (type == REG_CODE)
		return (T_REG);
	else if (type == DIR_CODE)
		return (get_dir_size(byte));
	else if (type == IND_CODE)
		return (IND_CODE);
	return (0xFF);
}

uint8_t select_type(uint8_t type)
{
	if (type == REG_CODE)
		return (REG_CODE);
	else if (type == DIR_CODE)
		return (DIR_CODE);
	else if (type == IND_CODE)
		return (IND_CODE);
	return (0xFF);
}

int		type_args(t_vm *vm, int num_of_arg, uint8_t *type)
{
	uint8_t	size_type;
	int 	addr;

	addr = vm->car->pc;
	size_type = vm->arena[addr + 1];
	if (num_of_arg == 1)
	{
		size_type = select_args(size_type, 1);
		*type = select_type(size_type >> 6);
		size_type = select_size(size_type >> 6, vm->car->op_code);
	}
	else if (num_of_arg == 2)
	{
		size_type = select_args(size_type, 2);
		*type = select_type(size_type >> 4);
		size_type = select_size(size_type >> 4, vm->car->op_code);
	}
	else if (num_of_arg == 3)
	{
		size_type = select_args(size_type, 3);
		*type = select_type(size_type >> 2);
		size_type = select_size(size_type >> 2, vm->car->op_code);
	}
	return (size_type);
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
	addr = get_addr(vm->car->move); // start address of argument (or current position car.)
	sign = (arena[addr] >> 7) ? 1 : 0;
	shift = 0;
	while (size)
	{
		if (sign)
		{
			addr = get_addr(vm->car->move + size - 1);
			value = value + ((arena[addr] ^ 0xFF) << shift);
			shift = shift + 8;
		}
		else
		{
			addr = get_addr(vm->car->move + size - 1);
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
		cur_addr = get_addr(addr + size - 1);
		byte = value >> shift;
		arena[cur_addr] = byte;
		shift = shift + 8;
		size--;
	}
}

int 	arg_value(t_vm *vm, int type, int size)
{
	int 	value;

	value = 0;
	if (type == REG_CODE)
		value = vm->car->registers[read_byte(vm, vm->car->move ) - 1]; // vm->car->move - 1 is number of reg, because -1
	else if (type == DIR_CODE)
		value = get_value(vm, size);
	else if (type == IND_CODE)
	{
		value = get_value(vm, T_IND); // get address from to read
		if (vm->car->op_code != 0x0e) //lldi
			value = value % IDX_MOD;
		vm->car->tmp_addr = vm->car->move; //save address to tmp var
		vm->car->move = value;
		value = get_value(vm, size);
		vm->car->move = vm->car->tmp_addr;
	}
	return (value);
}

int 	get_arg(t_vm *vm, int num_of_arg)
{
	int arg;
	int size;
	uint8_t type;

	arg = 0;
	if (num_of_arg == 1)
	{
		type = vm->car->args_type->arg_1;
		size = vm->car->args_size->arg_1;
		arg = arg_value(vm, type, size);
	}
	else if (num_of_arg == 2)
	{
		type = vm->car->args_type->arg_2;
		size = vm->car->args_size->arg_2;
		arg = arg_value(vm, type, size);
	}
	else if (num_of_arg == 3)
	{
		type = vm->car->args_type->arg_3;
		size = vm->car->args_size->arg_3;
		arg = arg_value(vm, type, size);
	}
	return (arg);
}

void	check_cycle_exec(t_vm *vm, uint8_t byte, void (*f)(t_vm *))
{
	if (vm->car->cycle_to_exec == -1)
		vm->car->cycle_to_exec = get_cycle_to_exec(byte) - 1;
	// may to do check errors here
	if (vm->car->cycle_to_exec > 0 )
		vm->car->cycle_to_exec--;
	else if (vm->car->cycle_to_exec == 0)
	{
		vm->car->op_code = byte;
		if ((vm->car->args_size->arg_1 = type_exception(byte)))
			vm->car->args_type->arg_1 = DIR_CODE;
		else
		{
			vm->car->args_size->arg_1 = type_args(vm, 1, &vm->car->args_type->arg_1);
			vm->car->args_size->arg_2 = type_args(vm, 2, &vm->car->args_type->arg_2);
			vm->car->args_size->arg_3 = type_args(vm, 3, &vm->car->args_type->arg_3);
		}
		f(vm);
		vm->car->cycle_to_exec = -1;
		/*
		if (!vm->car->next)
		{
			vm->cycle--;
			vm->cycle_left--;
		}
		 */
	}
}

int		slct_instr(unsigned char byte, t_vm *vm)
{
	int 			flag;

	flag = 0;
	if (byte == 0x01)
		check_cycle_exec(vm, byte, live);
	else if (byte == 0x02)
		check_cycle_exec(vm, byte, ld);
	else if (byte == 0x03)
		check_cycle_exec(vm, byte, st);
	else if (byte == 0x04)
		check_cycle_exec(vm, byte, add);
	else if (byte == 0x05)
		check_cycle_exec(vm, byte, sub);
	else if (byte == 0x06)
		check_cycle_exec(vm, byte, and);
	else if (byte == 0x07)
		check_cycle_exec(vm, byte, or);
	else if (byte == 0x08)
		check_cycle_exec(vm, byte, xor);
	else if (byte == 0x09)
		check_cycle_exec(vm, byte, zjmp);
	else if (byte == 0x0a)
		check_cycle_exec(vm, byte, ldi);
	else if (byte == 0x0b)
		check_cycle_exec(vm, byte, sti);
	else if (byte == 0x0c)
		check_cycle_exec(vm, byte, ffork);
	else if (byte == 0x0d)
		check_cycle_exec(vm, byte, lld);
	else if (byte == 0x0e)
		check_cycle_exec(vm, byte, lldi);
	else if (byte == 0x0f)
		check_cycle_exec(vm, byte, lfork);
	else if (byte == 0x10)
		check_cycle_exec(vm, byte, aff);
	else
		flag = -1;
	return (flag);
}
