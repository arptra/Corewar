#include "parse.h"

int	get_dir_size(uint8_t byte)
{
	if (byte == 0x01)
		return (4);
	else if (byte == 0x02)
		return (4);
	else if (byte == 0x03)
		return (4);
	else if (byte == 0x04)
		return (4);
	else if (byte == 0x05)
		return (4);
	else if (byte == 0x06)
		return (4);
	else if (byte == 0x07)
		return (4);
	else if (byte == 0x08)
		return (4);
	else if (byte == 0x09)
		return (2);
	else if (byte == 0x0a)
		return (2);
	else if (byte == 0x0b)
		return (2);
	else if (byte == 0x0c)
		return (2);
	else if (byte == 0x0d)
		return (4);
	else if (byte == 0x0e)
		return (2);
	else if (byte == 0x0f)
		return (2);
	else if (byte == 0x10)
		return (4);
	return (0);
}