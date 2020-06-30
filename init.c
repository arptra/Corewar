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
	if (bytes_to_int(vm->current->fd, 4, 16) != 0)
	{
		write(2,"Here should be zero bytes\n",30);
		exit (-1);
	}
	while (read_byte_fd(vm->current->fd, &byte) == 0)
	{
		vm->arena[addr + i++] = byte;
	}
	if (i != vm->current->cs)
	{
		write(2,"Champion's actual code size does not match declared code size\n",62);
		exit(-1);
	}
}

void	placed_players(t_vm *vm)
{
	int				cnt;
	int				addr;

	addr = 0;
	cnt = 0;
	while (++cnt <= vm->players->num_players)
	{
		placed_player(addr,cnt,vm);
		addr += MEM_SIZE / vm->players->num_players;
	}
}

t_args		*init_args()
{
	t_args *args;

	args = (t_args*)malloc(sizeof(t_args));
	args->arg_1 = 0;
	args->arg_2 = 0;
	args->arg_3 = 0;
	return (args);
}

t_carriage	*init_cursor()
{
	t_carriage	*cursor;

	cursor = (t_carriage*)malloc(sizeof(t_carriage));
	cursor->player = NULL;
	cursor->player_num = 0;
	cursor->start_addr = 0;
	cursor->cur_addr = 0;
	return (cursor);
}

t_vm	*init_vm(int argc, char **argv)
{
	t_vm	*vm;
	uint8_t	*arena;

	vm = (t_vm*)malloc((sizeof(t_vm)));
	vm->carriage = init_cursor();
	vm->carriage->args = init_args();
	if (!(arena = ft_memalloc(MEM_SIZE)))
		exit(-1);
	vm->arena = arena;
	vm->cur_num_player = 0;
	vm->players = parse_args(argc, argv);
	placed_players(vm);
	return (vm);
}