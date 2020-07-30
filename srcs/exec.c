#include "../incl/parse.h"

int 	set_carriage(t_vm *vm)
{
	t_carriage	*car;
	int			num_player;

	num_player = 1;
	while (num_player <= vm->players_num)
	{
		car = init_carriage();
		car->args_size = init_args_size();
		car->args_type = init_args_type();
		car->num = num_player;
		car->start_addr = get_player(vm, num_player)->start_addr;
		car->pc = car->start_addr;
		car->move = car->pc;
		car->registers[0] = -num_player;
		car->p = get_player(vm, num_player);
		add_car(&(vm->car), car);
		if (vm->flag_vis == 1)
			print_add_carriage(vm, num_player, car);
		num_player++;
	}
	return (0);
}

int 	exec_op(t_vm *vm)
{
	int			addr;
	t_carriage	*cursor;
	uint8_t 	*arena;
	uint8_t 	byte;

	cursor = vm->car;
	arena = vm->arena;
	addr = cursor->pc;
	if (cursor->cycle_to_exec == -1)
	{
		byte = arena[addr];
		cursor->op_code = byte;
	}
	slct_instr(cursor->op_code, vm);
	return (0);
}

void 	exec_cycle(t_vm *vm)
{
	while (vm->car)
	{
		exec_op(vm);
		vm->car->move = get_addr(vm->car->move);
		if (vm->flag_vis == 1 && vm->car->move - vm->car->pc != 0)
			print_move_carriage(vm, vm->car->p->cnum, vm->car->move - vm->car->pc);
		vm->car->pc = vm->car->move;
		vm->car = vm->car->next;
	}
}

void	exec(t_vm *vm)
{
	set_carriage(vm);
	vm->head = vm->car;
	while (vm->cars_num)
	{
		vm->cycle++;
		vm->cycle_left++;
		if (vm->d_mod == 2 || vm->d_mod == 1)
			printf("It is now cycle %d\n", vm->cycle);
		exec_cycle(vm);
		if (vm->cycle_to_die == vm->cycle_left || vm->cycle_to_die <= 0)
			check(vm);
		vm->car = vm->head;
		if (vm->nbr_cycles && vm->cycle == vm->nbr_cycles)
		{
			print_arena(vm->arena, MEM_SIZE);
			exit(0);
		}
	}
}