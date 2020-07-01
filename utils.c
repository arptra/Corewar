#include "parse.h"

void	show_byte(unsigned char byte, t_vm *vm)
{
	char *sym;

	sym = ft_itoa_base(byte, 16);
	ft_putstr(sym);
	free(sym);
}

int		read_byte_fd(int fd, unsigned char *byte)
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
	while (++i < nbytes && read_byte_fd(player->fd, &byte) == 0)
		f(byte, vm);
	return (i);
}

uint8_t read_byte(t_vm *vm, int addr) // addr - step that need to jump, for read byte from it addr
{
	uint8_t *arena;
	int 	cur_addr;

	arena = vm->arena;
	cur_addr = vm->carriage->pc;
	return (arena[cur_addr + addr]);
}
