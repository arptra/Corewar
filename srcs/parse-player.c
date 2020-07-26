#include "../incl/parse.h"

t_file_info		*parse_player(char *player_name, t_vm *vm)
{
	int				fd;
	t_file_info		*info;
	long int		magic;

	if (!(ft_strequ(ft_strrchr(player_name, (int)'.'), ".cor")))
		ft_error(2, vm);
	if ((fd = open(player_name, O_RDONLY)) == -1)
		ft_error(3, vm);
	if (!(info = (t_file_info*)ft_memalloc(sizeof(t_file_info))))
		exit(-1);
	magic = bytes_to_int(fd, 4, 16, vm);
	if (magic != COREWAR_EXEC_MAGIC)
		ft_error(4, vm);
	info->cn = bytes_to_string(fd, PROG_NAME_LENGTH, vm);
	if (bytes_to_int(fd, 4, 16, vm) != 0)
		ft_error(5, vm);
	if ((info->cs = bytes_to_int(fd, 4, 16, vm)) > CHAMP_MAX_SIZE)
		ft_error(6, vm);
	info->cc = bytes_to_string(fd, COMMENT_LENGTH, vm);
	info->fd = fd;
	return (info);
}

int				ft_get_current_num(t_file_info *players, int candidate)
{
	t_file_info		*temp1;
	int				flag;

	while (1)
	{
		temp1 = players;
		flag = 1;
		while (temp1)
		{
			if (temp1->cnum == candidate)
			{
				candidate++;
				flag = 0;
			}
			temp1 = temp1->next;
		}
		if (flag)
			return (candidate);
	}
}

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

void		place_player(int addr, int num_player, t_vm *vm)
{
	uint8_t byte;
	int		i;

	i = 0;
	vm->current = get_player(vm, num_player);
	vm->current->start_addr = addr;

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
