#include "../incl/parse.h"

void	place_players(t_vm *vm)
{
	int				cnt;
	int				addr;
	int				cnt2;

	addr = 0;
	cnt = 0;
	cnt2 = 0;
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
	// args->arg_1 = 0;
	// args->arg_2 = 0;
	// args->arg_3 = 0;
	return (args);
}

t_args_type		*init_args_type()
{
	t_args_type *args;

	args = (t_args_type*)ft_memalloc(sizeof(t_args_type));
	// args->arg_1 = 0;
	// args->arg_2 = 0;
	// args->arg_3 = 0;
	return (args);
}

t_carriage	*init_carriage()
{
	t_carriage	*car;

	car = (t_carriage*)malloc(sizeof(t_carriage));
	// car->start_addr = 0;
	// car->pc = 0;
	// car->move = 0;
	car->cycle_to_exec = -1;
	// car->carry = 0;
	return (car);
}

t_vm	*init_vm(int argc, char **argv)
{
	t_vm	*vm;
	uint8_t	*arena;

	vm = (t_vm*)ft_memalloc((sizeof(t_vm)));
	vm->car = NULL;
	//vm->car->args_size = init_args_size();
	//vm->car->args_type = init_args_type();
	if (!(arena = ft_memalloc(MEM_SIZE)))
		exit(-1);
	vm->arena = arena;
	vm = parse_args(argc, argv, vm);//need check
	vm->cycle_to_die = CYCLE_TO_DIE;
	// vm->flag_vis = 1;
	place_players(vm);
	vm->cars_num = vm->players_num;
	return (vm);
}