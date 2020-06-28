#include "parse.h"

void	show_byte(unsigned char byte, t_vm *vm)
{
	char *sym;

	sym = ft_itoa_base(byte, 16);
	ft_putstr(sym);
	free(sym);
}

int		read_byte(int fd, unsigned char *byte)
{
	if (read(fd, &(*byte), 1) > 0)
		return (0);
	else
		return (-1);
}

void	nthng(unsigned char byte, t_vm *vm)
{
}

int 	read_nbytes(t_vm *vm, int nbytes, void (*f)(unsigned char, t_vm *vm))
{
	int				i;
	unsigned char	byte;
	t_file_info		*player;

	i = -1;
	player = vm->current;
	while (++i < nbytes && read_byte(player->fd, &byte) == 0)
		f(byte, vm);
	return (i);
}

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

void	slct_instr(unsigned char byte, t_vm *vm)
{
	unsigned char	code_type_args;
	uint8_t			arg_1;
	uint16_t		arg_2;
	uint16_t		arg_3;
	t_file_info		*player;

	player = vm->current;
	if (byte == 0x0b)
	{
		read_byte(player->fd, &code_type_args);
		read_byte(player->fd, &arg_1);
		printf("intsr: sti\ncode_types_args: %x\n\t arg_1: %x -> type: %x",code_type_args, arg_1, args_type(code_type_args, 1));
	}
}
