#include "parse.h"

int main(int argc, char **argv)
{
	t_vm			*vm;

	if (argc == 1)
	{
		write(1,"usage:",6);
		exit(-1);
	}
	vm = init_vm(argc, argv);
	vm->cursor = vm->players;
	placed_player(0, 1, vm);
	print_arena(vm->arena, MEM_SIZE);
	printf("\n");
	return (0);
}