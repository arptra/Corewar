/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: u18188899 <u18188899@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 21:05:28 by student           #+#    #+#             */
/*   Updated: 2020/08/01 18:24:40 by u18188899        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "../vm_ft_printf/ft_printf.h"
# include "../libft/libft.h"
# include "op.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdint.h>

# define T_RD  3
# define T_RI  5
# define T_DI  6
# define T_RDI 7

# define SEP  '"'

typedef struct			s_file_info
{
	int					fd;
	char				*cn;
	int					cs;
	char				*cc;
	int					cnum;
	int					players_num;
	int					start_addr;
	struct s_file_info	*next;
}						t_file_info;

typedef struct			s_args_size
{
	int					arg_1;
	int					arg_2;
	int					arg_3;
}						t_args_size;

typedef struct			s_args_type
{
	uint8_t				arg_1;
	uint8_t				arg_2;
	uint8_t				arg_3;
}						t_args_type;

typedef struct			s_carriage
{
	int					num;
	uint8_t				op_code;
	int					start_addr;
	int					pc;
	int					last_live;
	int					registers[REG_NUMBER];
	int					move;
	int					tmp_addr;
	int					cycle_to_exec;
	int					carry;
	t_args_size			*a_s;
	t_args_type			*a_t;
	t_file_info			*p;
	struct s_carriage	*next;
}						t_carriage;

typedef struct			s_vm
{
	t_file_info			*players;
	int					players_num;
	uint8_t				*arena;
	t_file_info			*current;
	t_file_info			*last_live;
	int					car_count;
	int					lives;
	int					checks;
	int					cycle_to_die;
	int					cycle_left;
	int					cycle;
	int					cars_num;
	int					flag_vis;
	int					nbr_cycles;
	int					itrtr;
	int					d_mod;
	int					aff;
	t_carriage			*car;
	t_carriage			*head;
}						t_vm;

unsigned char			byte(int fd, t_vm	*vm);
long int				bytes_to_int(int fd, int n, int base, t_vm	*vm);
char					*bytes_to_string(int fd, int n_bytes, t_vm	*vm);
int						ft_get_current_num(t_file_info *players, int candidate);
void					ft_sort_players(t_vm	*vm);
t_vm					*ft_players(t_vm *vm, int players_num);
t_vm					*parse_args(int argc, char **argv, t_vm *vm);
int						read_byte_fd(int fd, unsigned char *byte);
void					slct_instr(unsigned char byte, t_vm *vm);
int						type_args(t_vm *vm, int num_of_arg, uint8_t *type);
void					print_byte_by_ptr(void *memory);
void					print_arena(void *arena, size_t size);
t_vm					*init_vm(int argc, char **argv);
void					place_player(int addr, int num_player, t_vm *vm);
t_file_info				*get_player(t_vm *vm, int num_player);
int						set_carriage(t_vm *vm);
uint8_t					read_byte(t_vm *vm, int addr);
void					exec(t_vm *vm);
int						get_arg(t_vm *vm, int num_of_arg);
int						get_value(t_vm *vm, int size);
void					put_value(t_vm *vm, int addr, int size, int value);
int						get_dir_size(uint8_t byte);
int						get_cycle_to_exec(uint8_t byte);
void					check_cycle_exec(t_vm *vm, uint8_t byte,\
											void (*f)(t_vm *));
int						type_exception(uint8_t byte);
t_carriage				*init_carriage();
t_args_size				*init_args_size();
t_args_type				*init_args_type();
void					add_car(t_carriage **car, t_carriage *new_car);
int						get_addr(int addr);
t_carriage				*copy_carriage(t_carriage *car, int addr);
void					delete_car(t_vm *vm);
int						check_for_die(t_vm *vm, t_carriage *car);
int						ind_move(int type, int size);
void					check(t_vm *vm);
int						check_args_type(uint8_t byte, t_vm *vm);
int						conjunction(int vm_arg, int ref_arg,\
										int step, t_vm *vm);
/*
** instructions
*/
void					sti(t_vm *vm);
void					live(t_vm *vm);
void					ld(t_vm *vm);
void					zjmp(t_vm *vm);
void					add(t_vm *vm);
void					aff(t_vm *vm);
void					and(t_vm *vm);
void					ldi(t_vm *vm);
void					lld(t_vm *vm);
void					lldi(t_vm *vm);
void					or(t_vm *vm);
void					sub(t_vm *vm);
void					xor(t_vm *vm);
void					st(t_vm *vm);
void					ffork(t_vm *vm);
void					lfork(t_vm *vm);
/*
** end instruction
*/
void					ft_error(int code, t_vm *vm);
unsigned char			byte(int fd, t_vm *vm);
void					ft_swap_players(t_file_info *temp1,
								t_file_info *temp2,
								t_vm *vm);
t_vm					*ft_parse_flags(int argc, char **argv, t_vm *vm);
t_file_info				*parse_player(char *player_name, t_vm *vm);
/*
** VIS_FUNC
*/
void					print_add_carriage(t_vm *vm, int player_id,\
											t_carriage *car);
void					print_kill_carriage(t_vm *vm,\
											t_carriage *car);
void					print_write_memory(t_vm *vm, int player_id,\
											int address,\
											int32_t reg_value);
void					print_move_carriage(t_vm *vm, const int player_id,\
												int offset);
void					print_add_player(t_vm *vm, const int player_id,\
											const char *name, int address);
void					print_declare_winner(t_vm *vm);
/*
** END VIS FUNC
*/
void					players_intro(t_vm *vm);
/*
** delete func
*/
void					free_car(t_carriage **car);
void					ft_free_vm(t_vm **vm);
#endif
