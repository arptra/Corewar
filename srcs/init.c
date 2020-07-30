#include "../incl/parse.h"

void			place_players(t_vm *vm)
{
	int				cnt;
	int				addr;

	addr = 0;
	cnt = 0;
	while (++cnt <= vm->players_num)
	{
		place_player(addr,cnt,vm);
		addr += MEM_SIZE / vm->players_num;
		if (vm->flag_vis == 1)
			print_add_player(vm,
					0,
					vm->current->cnum,
					vm->current->cn,
					vm->current->start_addr);
	}
	vm->last_live = get_player(vm, 1);
}

t_args_size		*init_args_size()
{
	t_args_size *args;

	args = (t_args_size*)ft_memalloc(sizeof(t_args_size));
	return (args);
}

t_args_type		*init_args_type()
{
	t_args_type *args;

	args = (t_args_type*)ft_memalloc(sizeof(t_args_type));
	return (args);
}

t_carriage		*init_carriage()
{
	t_carriage	*car;

	car = (t_carriage*)malloc(sizeof(t_carriage));
	car->cycle_to_exec = -1;
	return (car);
}

t_vm			*init_vm(int argc, char **argv)
{
	t_vm	*vm;
	uint8_t	*arena;

	vm = (t_vm*)ft_memalloc((sizeof(t_vm)));
	vm->car = NULL;
	vm->head = NULL;
	if (!(arena = ft_memalloc(MEM_SIZE)))
		exit(-1);
	vm->arena = arena;
	vm->d_mod = -1;
	vm = parse_args(argc, argv, vm);
	vm->cycle_to_die = CYCLE_TO_DIE;
	place_players(vm);
	vm->cars_num = vm->players_num;
	return (vm);
}