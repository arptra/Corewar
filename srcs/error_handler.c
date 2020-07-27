#include "../incl/parse.h"

int error_handler(int error, t_vm *vm)
{
	/* if something bad and
	 * exec of vm should stop
	 * free everything and
	 * exit with print in stdout type of error
	 */
	return (0);
}

void				ft_error(int code, t_vm *vm)
{
	int				fd;
	char			buf;
	int				i1;

	i1 = 1;
	ft_free_vm(vm);
	if ((fd = open("txt/errors.txt", O_RDONLY)) == -1)
		exit(-1);
	while (read(fd, &buf, 1))
	{
		if (buf == '\n' && i1 > code)
			break;
		if (i1 == code)
			write(2, &buf, 1);
		if (buf == '\n')
			i1++;
	}
	close(fd);
	exit(code);
}