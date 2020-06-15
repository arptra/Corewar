#include "parse.h"

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

/* print n bytes */
void	print_bytes(int fd, int n)
{
	int i;

	i = -1;
	while (++i < n)
		print_byte(fd);
}

unsigned char	byte(int fd)
{
	unsigned char byte;

	if (read(fd, &byte, 1) > 0)
		return (byte);
	else
	{
		write(2,"Error: could not read from file with champion\n",100);
		exit(-1);
	}
}

long int	bytes_to_int(int fd, int n, int base)
{
	int i;
	long int	res;
	int	bt;

	res = 0;
	i = -1;
	while (++i < n)
	{
		bt = (int)(byte(fd));
		res = base * base * res + bt / 16 * base + bt % 16;
	}
	return (res);
}

char	*bytes_to_string(int fd, int n_bytes)
{
	int i;
	char	*res;
	int		bt;
	char			*chars;

	// chars = "0123456789abcdef";
	if (!(res = ft_strnew(n_bytes * 2)))
		exit(-1);
	i = -1;
	while (++i < n_bytes)
	{
		res[i] = (char)byte(fd);
	}
	return (res);
}

t_file_info		*parse_player(char *player_name, int player_num, int nbr_cycles)
{
	int fd;
	t_file_info		*info;
	long int				magic;

	if (!(ft_strequ(ft_strrchr(player_name,(int)'.'),".cor")))
	{
		write(2,"Error: file with champion code not properly named\n",100);
		exit (-1);
	}
	if ((fd = open(player_name, O_RDONLY)) == -1)
	{
		write(2,"Error: file with champion code could not be opened\n",100);
		exit (-1);
	}
	if (!(info = (t_file_info*)ft_memalloc(sizeof(t_file_info))))
		exit(-1);
	magic = bytes_to_int(fd, 4, 16);
	info->cn = bytes_to_string(fd, PROG_NAME_LENGTH);
	if (magic != COREWAR_EXEC_MAGIC)
	{
		write(2,"Error: this is not a champion\n",30);
		exit (-1);
	}
	if ((info->cs = bytes_to_int(fd, 8, 10)) > CHAMP_MAX_SIZE)
	{
		write(2,"Error: this champion is too big\n",32);
		exit (-1);
	}
	info->cc = bytes_to_string(fd, COMMENT_LENGTH);
	info->cnum = player_num;
	info->nbr_cycles = nbr_cycles;
	return (info);
}

t_file_info		*parse_args(int argc, char **argv)
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
	players = NULL;
	if (ft_strequ(argv[1],"-dump"))
	{
		if ((nbr_cycles = ft_atoi(argv[2])) < 1)
		{
			write(2,"Error: nbr_cycles should be positive integer\n",46);
			exit (-1);
		}
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
			{
				write(2,"Error: -n flag not properly used\n",46);
				exit (-1);
			}
		}
		else
			player_num = 0;
		if (players == NULL)
		{
			players = parse_player(argv[i], player_num, nbr_cycles);
			temp = players;
		}
		else
		{
			temp->next = parse_player(argv[i], player_num, nbr_cycles);
			temp=temp->next;
		}
	}
	if (num_players > MAX_PLAYERS)
	{
		write(2,"Error: too much players for game\n",34);
		exit (-1);
	}
	return (players);
}

int main(int argc, char **argv)
{
	t_file_info		*players;

	players = parse_args(argc, argv);
	// print_bytes(fd, 8);
	return (0);
}