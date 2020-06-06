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

int main(int argc, char **argv)
{
	int fd;

	fd = open(argv[1], O_RDONLY);
	print_bytes(fd, 4);
}