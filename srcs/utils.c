#include "../incl/parse.h"

int		read_byte_fd(int fd, unsigned char *byte)
{
	if (read(fd, &(*byte), 1) > 0)
		return (0);
	else
		return (-1);
}

uint8_t read_byte(t_vm *vm, int addr) // addr - step that need to jump, for read byte from it addr
{
	uint8_t *arena;

	arena = vm->arena;
	addr = get_addr(addr);
	return (arena[addr]);
}

t_carriage	*copy_carriage(t_carriage *car, int addr)
{
	t_carriage *new_car;
	int 		i;

	new_car = init_carriage();
	new_car->args_size = init_args_size();
	new_car->args_type = init_args_type();
	new_car->move = get_addr(addr + car->pc);
	new_car->pc = new_car->move;
	new_car->carry = car->carry;
	new_car->last_live = car->last_live;
	i = -1;
	while (++i < REG_NUMBER)
		new_car->registers[i] = car->registers[i];
	return (new_car);
}

void	add_car(t_carriage **car, t_carriage *new_car)
{
	if (new_car)
		new_car->next = *car;
	*car = new_car;
}

int	get_addr(int addr)
{
	addr = addr % MEM_SIZE;
	if (addr < 0)
		addr = addr + MEM_SIZE;
	return (addr);
}