#include "parse.h"

void	ft_free(t_vm *vm)
{
	return ;
}

void	ft_error(int code, t_vm *vm)
{
	int		fd;
	char	buf;
	int		i1;

	i1 = 0;
	ft_free(vm);
	if ((fd = open("errors.txt", O_RDONLY)) == -1)
		exit(-1);
	while (read(fd,&buf,1))
	{
		if (buf == '\n' && i1 > code)
			break;
		if (i1 == code)
			write(2,&buf,1);
		if (buf == '\n')
			i1++;
	}
	close(fd);
	exit(code);
}

/* print 1 byte */
int	print_byte(int fd)
{
	unsigned char byte;
	char *sym;

	if (read(fd, &byte, 1) > 0)
	{
		sym = ft_itoa_base(byte, 16);
		ft_putstr(sym);
		free(sym);
	}
	else
		exit (-1);
	return (1);
}

void	print_byte_by_ptr(void *memory)
{
	char *chars;
	int		int1;

	chars = "0123456789abcdef";
	int1 = *(uint8_t *)memory;
	write(1, &chars[int1 / 16], 1);
	write(1, &chars[int1 % 16], 1);
}

/* print n bytes */
void	print_bytes(int fd, int n)
{
	int i;

	i = -1;
	while (++i < n)
		print_byte(fd);
}

unsigned char	byte(int fd, t_vm *vm)
{
	unsigned char byte;

	if (read(fd, &byte, 1) > 0)
		return (byte);
	else
		ft_error(1, vm);
	return (0);
}

long int	bytes_to_int(int fd, int n, int base, t_vm *vm)
{
	int i;
	long int	res;
	int	bt;

	res = 0;
	i = -1;
	while (++i < n)
	{
		bt = (int)(byte(fd,vm));
		res = base * base * res + bt / 16 * base + bt % 16;
	}
	return (res);
}

char	*bytes_to_string(int fd, int n_bytes, t_vm *vm)
{
	int i;
	char	*res;

	if (!(res = ft_strnew(n_bytes * 2)))
		exit(-1);
	i = -1;
	while (++i < n_bytes)
	{
		res[i] = (char)byte(fd,vm);
	}
	return (res);
}

t_file_info		*parse_player(char *player_name, int player_num, int nbr_cycles,t_vm *vm)
{
	int fd;
	t_file_info		*info;
	long int				magic;

	if (!(ft_strequ(ft_strrchr(player_name,(int)'.'),".cor")))
		ft_error(2,vm);
	if ((fd = open(player_name, O_RDONLY)) == -1)
		ft_error(3,vm);
	if (!(info = (t_file_info*)ft_memalloc(sizeof(t_file_info))))
		exit(-1);
	magic = bytes_to_int(fd, 4, 16,vm);
	if (magic != COREWAR_EXEC_MAGIC)
		ft_error(4,vm);
	info->cn = bytes_to_string(fd, PROG_NAME_LENGTH,vm);
	if (bytes_to_int(fd, 4, 16,vm) != 0)
		ft_error(5,vm);
	if ((info->cs = bytes_to_int(fd, 4, 16,vm)) > CHAMP_MAX_SIZE)
		ft_error(6,vm);
	info->cc = bytes_to_string(fd, COMMENT_LENGTH,vm);
	info->cnum = player_num;
	info->nbr_cycles = nbr_cycles;
	info->fd = fd;
	return (info);
}

int					ft_get_current_num(t_file_info *players, int candidate)
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

void				ft_swap_players(t_file_info *temp1, t_file_info *temp2,t_vm *vm)
{
	t_file_info			*temp3;

	if (!(temp3 = (t_file_info*)ft_memalloc(sizeof(t_file_info))))
		ft_error(-1,vm);
	temp3->cn = temp1->cn;
	temp3->cs = temp1->cs;
	temp3->cc = temp1->cc;
	temp3->cnum = temp1->cnum;
	temp3->fd = temp1->fd;

	temp1->cn = temp2->cn;
	temp1->cs = temp2->cs;
	temp1->cc = temp2->cc;
	temp1->cnum = temp2->cnum;
	temp1->fd = temp2->fd;

	temp2->cn = temp3->cn;
	temp2->cs = temp3->cs;
	temp2->cc = temp3->cc;
	temp2->cnum = temp3->cnum;
	temp2->fd = temp3->fd;

	free(temp3);
}

void				ft_sort_players(t_vm *vm)
{
	t_file_info			*temp1;
	t_file_info			*temp2;
	int					flag;

	while (1)
	{
		temp1 = vm->players;
		flag = 1;
		while (temp1->next)
		{
			temp2 = temp1->next;
			if (temp1->cnum > temp2->cnum)
			{
				ft_swap_players(temp1,temp2, vm);
				flag = 0;
			}
			else if (temp1->cnum == temp2->cnum)
				ft_error(7,vm);
			temp1=temp1->next;
		}
		if (flag)
			return ;
	}
}

t_vm *ft_players(t_vm *vm, int num_players)
{
	t_file_info		*temp1;
	int				cnt;

	temp1 = vm->players;
	cnt = 0;
	while (temp1)
	{
		if (!(temp1->cnum))
		{
			temp1->cnum = ft_get_current_num(temp1, cnt);
			cnt = temp1->cnum + 1;
		}
		if (temp1->cnum > num_players)
			ft_error(8,vm);
		temp1->num_players = num_players;
		temp1 = temp1->next;
	}
	ft_sort_players(vm);
	return (vm);
}

t_vm		*parse_args(int argc, char **argv,t_vm *vm)
{
	int			num_players;
	int			nbr_cycles;
	int			i;
	int			player_num;
	t_file_info		*players;
	t_file_info		*temp;

	nbr_cycles = -1;
	num_players = argc - 1;
	i=0;
	//players = NULL;//vm->players == NULL?
	if (ft_strequ(argv[1],"-dump"))
	{
		if ((nbr_cycles = ft_atoi(argv[2])) < 0)
			ft_error(9,vm);
		num_players = num_players - 2;
		i += 2;
	}
	while (++i < argc)
	{
		if (ft_strequ(argv[i],"-n"))	//if the current arg = flag -n
		{
			if ( ++i >= argc			// check if the next arg (player_num) absent
				|| (player_num = ft_atoi(argv[i])) <= 0	// check if the player_num is not correct
				|| player_num > (num_players -= 2)		// check if the player_num is not correct
				|| ++i >= argc			// check if the next arg (player_file) - absent
				)
			ft_error(10,vm);
		}
		else							//not necessary - equals to zero in moment of allocation
			player_num = 0;				//not necessary - equals to zero in moment of allocation
		if (vm->players == NULL)
		{
			vm->players = parse_player(argv[i], player_num, nbr_cycles,vm);
			temp = vm->players;
		}
		else
		{
			temp->next = parse_player(argv[i], player_num, nbr_cycles,vm);
			temp=temp->next;
		}
	}
	if (num_players > MAX_PLAYERS)
		ft_error(11,vm);
	vm->players = ft_players(vm->players, num_players);
	return (vm);
}

void	print_arena(void *arena, size_t size)
{
	size_t		i1;

	i1 = 0;
	while (i1 < size)
	{
		print_byte_by_ptr(arena + i1);
		i1++;
		// NEED TO BE CHANGED TO 32 BEFORE VALUATION!
		if (i1%64 == 0)
			write(1,"\n",1);
	}
	write(1,"\n",1);
}