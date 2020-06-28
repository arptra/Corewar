#include "parse.h"

t_file_info	*get_player(t_vm *vm, int num_player)
{
	t_file_info *player;
	int i;

	i = 1;
	player = vm->players;
	while(player && i < num_player)
	{
		player = player->next;
		i++;
	}
	return (player);
}

void		placed_player(int addr, int num_player, t_vm *vm)
{
	uint8_t byte;
	int		i;

	i = 0;
	vm->current = get_player(vm, num_player);
	read_nbytes(vm,4, nthng);
	while (read_byte(vm->current->fd, &byte) == 0)
		vm->arena[addr + i++] = byte;
}

void	placed_players(t_vm *vm)
{
	/* code here -> placed all players in memory */
}

t_vm	*init_vm(int argc, char **argv)
{
	t_vm	*vm;
	uint8_t	*arena;

	vm = (t_vm*)malloc((sizeof(t_vm)));
	if (!(arena = ft_memalloc(MEM_SIZE)))
		exit(-1);
	vm->arena = arena;
	vm->players = parse_args(argc, argv);
	placed_players(vm); //need to realize
}