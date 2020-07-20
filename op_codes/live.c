#include "../parse.h"

void	live(t_vm *vm)
{
	int player_num;

	vm->car->move += 1; //move on 1 byte from op code to args
	player_num = get_arg(vm, 1);
	vm->car->move += vm->car->args_size->arg_1;
	vm->car->last_live = vm->cycle;
	vm->lives++;
	if (player_num <= -1 && player_num >= -vm->players_num)
	{
		vm->last_live = get_player(vm, -player_num);
	}

	// print_arena(vm->arena, 32);
}