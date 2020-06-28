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
	vm->cursor = get_player(vm, num_player);
	read_nbytes(vm,4, nthng);
	while (read_byte(vm->cursor->fd, &byte) == 0)
		vm->arena[addr + i++] = byte;
}

t_vm	*init_vm(int argc, char **argv)
{
	t_vm	*vm;
	uint8_t	*arena;

	vm = (t_vm*)malloc((sizeof(t_vm)));
	if (!(arena = ft_memalloc(MEM_SIZE)))
		exit(-1);
	vm->arena = (uint8_t*)malloc(sizeof(uint8_t)*MEM_SIZE);
	vm->players = parse_args(argc, argv);
}