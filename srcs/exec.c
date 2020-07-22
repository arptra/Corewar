#include "../incl/parse.h"

/*
 * need to realize for all players
 * calculate addr where start bytecode of player
 */

int 	get_start_addr(int num_player)
{
	if (num_player == 1)
		return (0);
	return (-1);
}

int 	set_carriage(t_vm *vm, int num_player)
{
	t_carriage	*car;

	car = vm->car;
	car->start_addr = get_start_addr(num_player);
	car->pc = car->start_addr;
	car->registers[0] = -num_player;
	return (0);
}

int 	exec_op(t_vm *vm)
{
	int			addr;
	t_carriage	*cursor;
	uint8_t 	*arena;
	int 		error;
	uint8_t 	byte;

	cursor = vm->car;
	arena = vm->arena;
	addr = cursor->pc;
	if (cursor->cycle_to_exec == -1)
	{
		byte = arena[addr];
		cursor->op_code = byte;
	}
	error = slct_instr(cursor->op_code, vm);
	/* here error handler */
	error_handler(error, vm);
	/* if ok next op */
	return (0);
}

void	exec(t_vm *vm)
{
	int flag;

	flag = 1;
	vm->current = get_player(vm, vm->cur_num_player);
	set_carriage(vm, vm->cur_num_player);
	/* here will cycle that exec op_codes */
	vm->head = vm->car;
	if (vm->nbr_cycles)
	{
		while (vm->cars_num)
		{
			vm->cycle++;
			vm->cycle_left++;
			while (vm->car)
			{
				exec_op(vm);
				vm->car->move = get_addr(vm->car->move);
				vm->car->pc = vm->car->move;// jump to next instruction
/*
				if (vm->cycle == 14056)
				{
					int i = 510;
					printf("car_num->%d op_code = %x", vm->car->num, vm->car->op_code);
					while (i < 514)
						printf(" %x ", vm->arena[i++]);
					flag = 0;
					printf("\n");
				}
*/
				vm->car = vm->car->next;
			}
			if (flag == 0)
				exit(0);
			debug_info(vm);
			if (vm->cycle_to_die == vm->cycle_left || vm->cycle_to_die <= 0)
				check(vm);
			vm->car = vm->head;
		}
		//print_arena(vm->arena, MEM_SIZE);
	}
	else
	{
		while (vm->cars_num)
		{
			exec_op(vm);
			vm->car->pc = vm->car->move;// jump to next instruction
			vm->cycle++;
			vm->cycle_left++;
			if (vm->cycle_to_die == vm->cycle_left || vm->cycle_to_die <= 0)
				check(vm);
		}
	}
}