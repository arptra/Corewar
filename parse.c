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
		exit (-1);
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

unsigned char	byte(int fd)
{
	unsigned char byte;

	if (read(fd, &byte, 1) > 0)
		return (byte);
	else
		exit(-1);
}

long int	bytes_to_int(int fd, int n, int base)
{
	int i;
	long int	res;
	int	bt;

	res = 0;
	i = -1;
	while (++i < n)
	{
		bt = (int)(byte(fd));
		res = base * base * res + bt / 16 * base + bt % 16;
	}
	return (res);
}

char	*bytes_to_string(int fd, int n_bytes)
{
	int i;
	char	*res;
	int		bt;
	char			*chars;

	chars = "0123456789abcdef";
	if (!(res = ft_strnew(n_bytes * 2)))
		exit(-1);
	i = -1;
	while (++i < n_bytes)
	{
		bt = (int)byte(fd);
		res[2 * i] = chars[bt / 16];
		res[2 * i + 1] = chars[bt % 16];
	}
	return (res);
}

int main(int argc, char **argv)
{
	int fd;
	t_file_info		*info;
	long int				magic;

	if (!(info = (t_file_info*)ft_memalloc(sizeof(t_file_info))))
		exit(-1);
	fd = open(argv[1], O_RDONLY);
	magic = bytes_to_int(fd, 4, 16);
	if (magic != COREWAR_EXEC_MAGIC)
	{
		write(2,"Error: this is not a champion\n",30);
		exit (-1);
	}
	info->cn = bytes_to_string(fd, PROG_NAME_LENGTH);
	if ((info->cs = bytes_to_int(fd, 8, 10)) > CHAMP_MAX_SIZE)
	{
		write(2,"Error: this champion is too big\n",32);
		exit (-1);
	}
	// print_bytes(fd, 8);
	return (0);
}