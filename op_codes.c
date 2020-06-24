#include "parse.h"

void	show_byte(unsigned char byte)
{
	char *sym;

	sym = ft_itoa_base(byte, 16);
	ft_putstr(sym);
	free(sym);
}

int		read_op_codes(int fd, unsigned char *byte)
{
	if (read(fd, &(*byte), 1) > 0)
		return (0);
	else
		return (-1);
}

void	nthng(unsigned char byte)
{
}

int 	read_nbytes(int fd, int nbytes, void (*f)(unsigned char))
{
	int i;
	unsigned char byte;

	i = -1;
	while (++i < nbytes && read_op_codes(fd, &byte) == 0)
			f(byte);
	return (i);
}

void	slct_instr(unsigned char byte)
{
	if (byte == 0x0b)
		printf("sti");
}
