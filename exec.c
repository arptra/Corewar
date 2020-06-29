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

int 	set_cursor(t_vm *vm, int num_player)
{
	t_carriage	*cursor;

	cursor = vm->carriage;
	cursor->start_addr = get_start_addr(num_player);
	cursor->player_num = num_player;
	cursor->player = vm->current;
	cursor->cur_addr = cursor->start_addr;
	cursor->registers[0] = -num_player;
	return (0);
}

int 	exec_op(t_vm *vm)
{
	int			addr;
	t_carriage	*cursor;
	uint8_t 	*arena;
	int 		error;

	cursor = vm->carriage;
	arena = vm->arena;
	addr = cursor->cur_addr;
	error = slct_instr(arena[addr], vm);
	/* here error handler */
	error_handler(error, vm);
	/*if ok next op */
	return (0);
}

void	exec(t_vm *vm)
{
	vm->current = get_player(vm, vm->cur_num_player);
	set_cursor(vm, vm->cur_num_player);
	/* here will cycle that exec op_codes */
	exec_op(vm);

}