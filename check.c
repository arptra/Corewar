#include "parse.h"

int check_for_die(t_vm *vm)
{
	if (vm->cycle_to_die <= 0 || vm->cycle - vm->car->last_live >= vm->cycle_to_die)
		return (1);
	else
		return (0);
}

void	check(t_vm *vm)
{
	vm->checks++;
	if(check_for_die(vm))
		vm->cars_num--;
	if (vm->checks == MAX_CHECKS || vm->lives >= NBR_LIVE)
	{
		vm->cycle_to_die -= CYCLE_DELTA;
		vm->checks = 0;
	}
	vm->cycle_left = 0;
	vm->lives = 0;
}