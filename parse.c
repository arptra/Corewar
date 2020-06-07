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

// t_file_info			*ft_wrt_info(int fd)
// {
// 	t_file_info		*res;
// 	unsigned char	*byte;
// 	char			*sym;
// 	int				i1;

// 	while (read(fd, &byte, 4) > 0)
// 	{
// 		sym = ft_itoa_base(byte, 16);
// 		ft_putstr(sym);
// 		free(sym);
// 	}
// 	else
// 		return (NULL);
// 	return (res);
// }

int main(int argc, char **argv)
{
	int fd;
	t_file_info		*info;
	char			*magic;

	magic = ft_itoa_base(COREWAR_EXEC_MAGIC,16);
	ft_putstr(magic);
	ft_putstr("\n");
	fd = open(argv[1], O_RDONLY);
	info = ft_wrt_info(fd);
	print_bytes(fd, 4);
}