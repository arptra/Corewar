#include "parse.h"

void	free_car(t_carriage **car)
{
	free((*car)->args_size);
	free((*car)->args_type);
	free(*car);
}

void	ft_free_vm(t_vm *vm)
{
	t_vm	*temp;

	temp = vm;
	return ;
}