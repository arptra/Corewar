#include "../incl/parse.h"

t_args_type	*decode_arg(int arg)
{
	t_args_type *type;

	type = init_args_type();
	if (arg == T_REG)
		type->arg_1 = REG_CODE;
	else if (arg == T_DIR)
		type->arg_2 = DIR_CODE;
	else if (arg == T_IND)
		type->arg_3 = IND_CODE;
	else if (arg == (T_REG | T_DIR))
	{
		type->arg_1 = REG_CODE;
		type->arg_2 = DIR_CODE;
	}
	else if (arg == (T_REG | T_IND))
	{
		type->arg_1 = REG_CODE;
		type->arg_3 = IND_CODE;
	}
	else if (arg == (T_DIR | T_IND))
	{
		type->arg_2 = DIR_CODE;
		type->arg_3 = IND_CODE;
	}
	else if (arg == (T_REG | T_DIR | T_IND))
	{
		type->arg_1 = REG_CODE;
		type->arg_2 = DIR_CODE;
		type->arg_3 = IND_CODE;
	}
	return (type);
}

int check_reg(int arg, t_vm *vm, int step)
{
	int reg;

	if (arg == REG_CODE)
	{
		reg = read_byte(vm, step);
		if (1 <= reg && reg <= REG_NUMBER)
			return (1);
		return (0);
	}
	return (1);
}

int conjunction(int vm_arg, int ref_arg, int step, t_vm *vm)
{
	t_args_type *ref_type;
	int 		flag;

	flag = 0;
	ref_type = decode_arg(ref_arg);
	if (ref_type->arg_1 != 0 && ref_type->arg_1 == vm_arg)
		flag = 1;
	if (ref_type->arg_2 != 0 && ref_type->arg_2 == vm_arg)
		flag = 1;
	if (ref_type->arg_3 != 0 && ref_type->arg_3 == vm_arg)
		flag = 1;
	free(ref_type);
	flag += check_reg(vm_arg, vm, step);
	if (flag != 2)
		return (3);
	return (1);
}

int ind_move(int type, int size)
{
	if (type == IND_CODE)
		return (IND_SIZE);
	return (size);
}

int type_check(int arg_1, int arg_2, int arg_3, t_vm *vm)
{
	t_args_type *type;
	int 		step;
	t_args_type *check;

	type = vm->car->args_type;
	step = vm->car->move + 2; // op code + arg len = 2
	check = init_args_type();
	if (arg_1)
	{
		check->arg_1 = conjunction(type->arg_1, arg_1, step, vm);
		step += ind_move(type->arg_1, vm->car->args_size->arg_1);
	}
	if (arg_2)
	{
		check->arg_2 = conjunction(type->arg_2, arg_2, step, vm);
		step += ind_move(type->arg_2, vm->car->args_size->arg_2);
	}
	if (arg_3)
	{
		check->arg_3 = conjunction(type->arg_3, arg_3, step, vm);
		step += ind_move(type->arg_3, vm->car->args_size->arg_3);
	}
	vm->car->tmp_addr = step;
	if (check->arg_1 < 2 && check->arg_2 < 2 && check->arg_3 < 2)
	{
		free(check);
		return (1);
	}
	free(check);
	return (0);
}

int	check_args_type(uint8_t byte, t_vm *vm)
{
	if (byte == 0x01)
		return (1);
	else if (byte == 0x02)
		return (type_check(T_DI, T_REG, 0, vm));
	else if (byte == 0x03)
		return (type_check(T_REG, T_RI, 0, vm));
	else if (byte == 0x04)
		return (type_check(T_REG, T_REG, T_REG, vm));
	else if (byte == 0x05)
		return (type_check(T_REG, T_REG, T_REG, vm));
	else if (byte == 0x06)
		return (type_check(T_RDI, T_RDI, T_REG, vm));
	else if (byte == 0x07)
		return (type_check(T_RDI, T_RDI, T_REG, vm));
	else if (byte == 0x08)
		return (type_check(T_RDI, T_RDI, T_REG, vm));
	else if (byte == 0x09)
		return (1);
	else if (byte == 0x0a)
		return (type_check(T_RDI, T_RD, T_REG, vm));
	else if (byte == 0x0b)
		return (type_check(T_REG, T_RDI, T_RD, vm));
	else if (byte == 0x0c)
		return (1);
	else if (byte == 0x0d)
		return (type_check(T_DI, T_REG, 0, vm));
	else if (byte == 0x0e)
		return (type_check(T_RDI, T_RD, T_REG, vm));
	else if (byte == 0x0f)
		return (1);
	else if (byte == 0x10)
		return (type_check(T_REG, 0, 0, vm));
	return (0);
}