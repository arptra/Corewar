#include "parse.h"

/*
 * need to realize for all players
 * calculate addr where start bytecode of player
 */

int 	get_start_addr(int num_player)
{
	if (num_player == 1)
		return (0);
	return (-1);
}

int 	set_carriage(t_vm *vm, int num_player)
{
	t_carriage	*car;

	car = vm->car;
	car->start_addr = get_start_addr(num_player);
	car->pc = car->start_addr;
	car->registers[0] = -num_player;
	return (0);
}

int 	exec_op(t_vm *vm)
{
	int			addr;
	t_carriage	*cursor;
	uint8_t 	*arena;
	int 		error;

	cursor = vm->car;
	arena = vm->arena;
	addr = cursor->pc;
	error = slct_instr(arena[addr], vm);
	/* here error handler */
	error_handler(error, vm);
	/* if ok next op */
	return (0);
}

void	exec(t_vm *vm)
{
	vm->current = get_player(vm, vm->cur_num_player);
	set_carriage(vm, vm->cur_num_player);
	/* here will cycle that exec op_codes */
	if (vm->players->nbr_cycles)
	{
		while (vm->cars_num)
		{
			exec_op(vm);
			vm->car->pc = vm->car->move;// jump to next instruction
			vm->cycle++;
			vm->cycle_left++;
 			if (vm->cycle_to_die == vm->cycle_left || vm->cycle_to_die <= 0)
				check(vm);
		}
		print_arena(vm->arena, MEM_SIZE);
	}
	else
	{
		while (vm->cars_num)
		{
			exec_op(vm);
			vm->car->pc = vm->car->move;// jump to next instruction
			vm->cycle++;
			vm->cycle_left++;
			if (vm->cycle_to_die == vm->cycle_left || vm->cycle_to_die <= 0)
				check(vm);
		}
	}
}