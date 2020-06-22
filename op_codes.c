#include "parse.h"

int	read_op_codes(int fd, unsigned char *byte)
{
	if (read(fd, &(*byte), 1) > 0)
		return (0);
	else
		return (-1);
}