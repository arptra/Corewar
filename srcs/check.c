#include "../incl/parse.h"
#include "stdio.h"

int check_for_die(t_vm *vm, t_carriage *car)
{
	if (vm->cycle_to_die <= 0 || vm->cycle - car->last_live >= vm->cycle_to_die)
		return (1);
	else
		return (0);
}

void	delete_car(t_vm *vm)
{
	t_carriage	*cur;
	t_carriage	*prev;
	t_carriage	*del;

	prev = NULL;
	cur = vm->head;
	while (cur)
	{
		del = cur;
		if (check_for_die(vm,del) && vm->cars_num--)
		{
			cur = cur->next;
			if(vm->head == del)
				vm->head = cur;
			if(prev)
				prev->next = cur;
			if (vm->flag_vis == 1)
				print_kill_carriage(vm, del);
			if (vm->d_mod == 8)
				printf("Process %d hasn't lived for %d cycles (CTD %d)\n", del->num, vm->cycle, vm->cycle_to_die);
			free_car(&del);
		}
		else
		{
			prev = cur;
			cur = cur->next;
		}
	}
}

void	check(t_vm *vm)
{
	vm->checks++;
	delete_car(vm);
	if (vm->checks == MAX_CHECKS || vm->lives >= NBR_LIVE)
	{
		vm->cycle_to_die -= CYCLE_DELTA;
		vm->checks = 0;
		if (vm->d_mod == 2)
			printf("Cycle to die is now %d\n", vm->cycle_to_die);
	}
	vm->cycle_left = 0;
	vm->lives = 0;
}