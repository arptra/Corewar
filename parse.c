#include "parse.h"

/* print 1 byte */
int	print_byte(int fd)
{
	unsigned char byte;
	char *sym;

	if (read(fd, &byte, 1) > 0)
	{
		sym = ft_itoa_base(byte, 16);
		ft_putstr(sym);
		free(sym);
	}
	else
		return (-1);
	return (1);
}

/* print n bytes */
void	print_bytes(int fd, int n)
{
	int i;

	i = -1;
	while (++i < n)
		print_byte(fd);
}

int	byte(int fd)
{
	unsigned char byte;

	if (read(fd, &byte, 1) > 0)
		return (byte);
	else
		exit(-1);
}

long int	get_magic(int fd, int n)
{
	int i;
	long int	res;

	res = 0;
	i = -1;
	while (++i < n)
		res = 16 * 16 * res + (byte(fd));
	return (res);
}

int main(int argc, char **argv)
{
	int fd;
	t_file_info		*info;
	long int				magic;

	// print_bytes(fd, 4);
	fd = open(argv[1], O_RDONLY);
	magic = get_magic(fd, 4);
	if (magic != COREWAR_EXEC_MAGIC)
		write(2,"Error: this is not a champion",29);
	return (0);
}