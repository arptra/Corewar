#include "../incl/parse.h"

void	free_car(t_carriage **car)
{
	free((*car)->args_size);
	free((*car)->args_type);
	free(*car);
}