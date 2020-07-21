#include "parse.h"

void	free_car(t_carriage **car)
{
	if (*car)
	{
		free((*car)->args_size);
		free((*car)->args_type);
		free(*car);
	}
}