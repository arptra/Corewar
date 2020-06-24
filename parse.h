//
// Created by ai on 06.06.2020.
//

#ifndef COREWAR_PARSE_H
#define COREWAR_PARSE_H

#include "libft/libft.h"
#include "op.h"
#include "stdio.h"

typedef struct	s_file_info
{
	int 		fd;
	char 		*cn; /* CHAMPION NAME */
	unsigned int cs; /* CHAMPION CODE SIZE */
	char 		*cc; /* CHAMPION COMMENT */
	int			cnum;	/* CHAMPION NUMBER */
	int			nbr_cycles;		/* at the end of nbr_cycles of executions, 
								dump the memory on the standard output and
								quit the game. The memory must be dumped 
								in the hexadecimal format with 32 octets per line.  */
	struct s_file_info	*next;	/* next champion */
}				t_file_info;

typedef struct s_arena
{
	void *data;
	struct s_arena *start;
}			t_arena;


/* print 1 byte */
int	print_byte(int fd);
/* print n bytes */
void	print_bytes(int fd, int n);
unsigned char	byte(int fd);
long int	bytes_to_int(int fd, int n, int base);
char	*bytes_to_string(int fd, int n_bytes);
t_file_info		*parse_player(char *player_name, int player_num, int nbr_cycles);
int					ft_get_current_num(t_file_info *players, int candidate);
void				ft_sort_players(t_file_info *players);
t_file_info			*ft_players(t_file_info *players, int num_players);
t_file_info		*parse_args(int argc, char **argv);

int		read_op_codes(int fd, unsigned char *byte);
void	show_byte(unsigned char byte);
int 	read_nbytes(int fd, int nbytes, void (*f)(unsigned char));
void	slct_instr(unsigned char byte);
void	nthng(unsigned char byte);


#endif //COREWAR_PARSE_H
