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
	t_cursor	*cursor;

	cursor = vm->cursor;
	cursor->start_addr = get_start_addr(num_player);
	cursor->player_num = num_player;
	cursor->player = vm->current;
	cursor->cur_addr = cursor->start_addr;
	return (0);
}

int 	exec_op(t_vm * vm)
{
	int 	addr;
	t_cursor	*cursor;
	uint8_t 	*arena;
	int 		check;


	cursor = vm->cursor;
	arena = vm->arena;
	addr = cursor->cur_addr;
	check = slct_instr(arena[addr]);
	if (check == -1)
		return (-1);
	return (0);
}

void	exec(t_vm *vm)
{
	vm->current = get_player(vm, vm->cur_num_player);
	set_cursor(vm, vm->cur_num_player);
	/* here will cycle that exec op_codes */
	exec_op(vm);

}