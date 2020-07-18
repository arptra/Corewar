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
	if (bytes_to_int(vm->current->fd, 4, 16,vm) != 0)
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
		vm->players_num++;
	}
}

t_args_size		*init_args_size()
{
	t_args_size *args;

	args = (t_args_size*)malloc(sizeof(t_args_size));
	args->arg_1 = 0;
	args->arg_2 = 0;
	args->arg_3 = 0;
	return (args);
}

t_args_type		*init_args_type()
{
	t_args_type *args;

	args = (t_args_type*)malloc(sizeof(t_args_type));
	args->arg_1 = 0;
	args->arg_2 = 0;
	args->arg_3 = 0;
	return (args);
}

t_carriage	*init_carriage()
{
	t_carriage	*car;

	car = (t_carriage*)malloc(sizeof(t_carriage));
	car->start_addr = 0;
	car->pc = 0;
	car->move = 0;
	car->cycle_to_exec = -1;
	car->carry = 0;
	return (car);
}

t_vm	*init_vm(int argc, char **argv)
{
	t_vm	*vm;
	uint8_t	*arena;

	vm = (t_vm*)malloc((sizeof(t_vm)));
	vm->car = init_carriage();
	vm->car->args_size = init_args_size();
	vm->car->args_type = init_args_type();
	if (!(arena = ft_memalloc(MEM_SIZE)))
		exit(-1);
	vm->arena = arena;
	vm->cur_num_player = 0;
	vm->players_num = 0;
	vm = parse_args(argc, argv, vm);//need check
	vm->lives = 0;
	vm->checks = 0;
	vm->cycle = 0;
	vm->cycle_left = 0;
	vm->cycle_to_die = CYCLE_TO_DIE;
	placed_players(vm);
	vm->cars_num = vm->players_num;
	return (vm);
}