#include "parse.h"

int main(int argc, char **argv)
{
	t_vm			*vm;

	if (argc == 1)
	{
		write(1,"usage:\n",7);
		exit(-1);
	}
	vm = init_vm(argc, argv);
	// vm->current = vm->players;
	vm->cur_num_player = 1; /* select player */
	// placed_player(0, vm->cur_num_player, vm);
	print_arena(vm->arena, MEM_SIZE);
	// printf("\n");

	exec(vm);
	print_arena(vm->arena, MEM_SIZE);

	return (0);
}