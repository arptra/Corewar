#include "parse.h"

void	ft_usage_corewar(void)
{
	int		fd;
	char	buf;

	fd = open("usage_corewar.txt", O_RDONLY);
	if (fd == -1)
		exit(-1);
	while (read(fd,&buf,1))
		write(1,&buf,1);
	close(fd);
	exit(-1);
}


int main(int argc, char **argv)
{
	t_vm			*vm;

	if (argc == 1)
		ft_usage_corewar();
	vm = init_vm(argc, argv);
	// vm->current = vm->players;
	vm->cur_num_player = 1; /* select player */
	// placed_player(0, vm->cur_num_player, vm);
	//print_arena(vm->arena, MEM_SIZE);
	// printf("\n");
	exec(vm);
	printf("player %s won", vm->last_live->cn);
	/* do not need this stuff: */
	// print_arena(vm->arena, 32);

	return (0);
}