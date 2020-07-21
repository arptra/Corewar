#include "../incl/parse.h"

// int				print_byte(int fd)
// {
// 	unsigned char	byte;
// 	char			*sym;

// 	if (read(fd, &byte, 1) > 0)
// 	{
// 		sym = ft_itoa_base(byte, 16);
// 		ft_putstr(sym);
// 		free(sym);
// 	}
// 	else
// 		exit (-1);
// 	return (1);
// }

// void			print_bytes(int fd, int n)
// {
// 	int				i;

// 	i = -1;
// 	while (++i < n)
// 		print_byte(fd);
// }

void			print_byte_by_ptr(void *memory)
{
	char			*chars;
	int				int1;

	chars = "0123456789abcdef";
	int1 = *(uint8_t *)memory;
	write(1, &chars[int1 / 16], 1);
	write(1, &chars[int1 % 16], 1);
}

unsigned char	byte(int fd, t_vm *vm)
{
	unsigned char	byte;

	if (read(fd, &byte, 1) > 0)
		return (byte);
	else
		ft_error(1, vm);
	return (0);
}

long int		bytes_to_int(int fd, int n, int base, t_vm *vm)
{
	int				i;
	long int		res;
	int				bt;

	res = 0;
	i = -1;
	while (++i < n)
	{
		bt = (int)(byte(fd, vm));
		res = base * base * res + bt / 16 * base + bt % 16;
	}
	return (res);
}

char			*bytes_to_string(int fd, int n_bytes, t_vm *vm)
{
	int				i;
	char			*res;

	if (!(res = ft_strnew(n_bytes * 2)))
		exit(-1);
	i = -1;
	while (++i < n_bytes)
	{
		res[i] = (char)byte(fd, vm);
	}
	return (res);
}

void			print_arena(void *arena, size_t size)
{	
	size_t			i1;

	i1 = 0;
	while (i1 < size)
	{
		print_byte_by_ptr(arena + i1);
		i1++;
		// NEED TO BE CHANGED TO 32 BEFORE VALUATION!
		if (i1%64 == 0)
			write(1, "\n", 1);
	}
	write(1, "\n", 1);
}