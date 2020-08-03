/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembler.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umoff <umoff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 13:37:24 by umoff             #+#    #+#             */
/*   Updated: 2020/07/02 14:01:15 by umoff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	ASSEMBLER_H
# define ASSEMBLER_H
# include <stdlib.h>
# include <stdint.h>
# include <fcntl.h>

# include "op.h"
# include "ft_ptintf.h"
# include "libft.h"
# include "options.h"
# include "asm_errors.h"

# define ML_GNL_LINE	10
# define ML_TOKEN		20
# define ML_ARGUMENT	30
# define ML_CMD_NAME 	40
# define ML_L_NAME		50
# define ML_S_CONTENT 	60
# define ML_LABEL		70
# define ML_CMD_NUM		80
# define ML_CHECK    	150

# define TKNZE_BREAK	1
# define TKNZE_CONT		2
# define ENDFILE		3
# define ENDLINE		4
# define NOTENDSTR		5

typedef enum	e_tkn_type
{
	NAME = 1,
	COMMENT_PROG,
	COMMAND,
	STRING,
	COMMENT,
	LABEL,
	ARGUMENT,
	ARGUMENT_LABEL,
	SEPARATOR,
	NEW_LINE,
	END
}				t_tkn_type;

typedef struct		s_tkn
{
	t_tkn_type		type;
	u_int32_t		row;
	u_int16_t		column;
	void			*content;
	struct s_tkn	*prev;
	struct s_tkn	*next;
}					t_tkn;

typedef struct		s_label
{
	char			*name;
	t_tkn			*tkn;
	struct s_label	*prev;
	struct s_label	*next;
}					t_label;

typedef struct		s_argument
{
	u_int8_t		type;
	void			*content;
	int				num;
}					t_arg;

typedef struct		s_parser_carriage
{
	u_int32_t		row;
	u_int16_t		column;
	char			*line;
}					t_pc;

typedef struct		s_tkn_sec
{
	_Bool			name;
	_Bool			comment;
	_Bool			comment_prog;
	_Bool			str_name;
	_Bool			str_comment;
	_Bool			command;
	_Bool			arg;
	_Bool			separator;
	_Bool			new_line;
}					t_tkn_sec;

static char	*g_type[] =
{
	"NAME",
	"COMMENT_PROG",
	"COMMAND",
	"STRING",
	"COMMENT",
	"LABEL",
	"ARGUMENT",
	"ARGUMENT_LABEL",
	"SEPARATOR",
	"NEW_LINE",
	"END",
};

t_tkn			*add_tkn(t_pc *pc, t_tkn **tkn_tail, t_label **label_tail,
																u_int8_t flag);
void			add_label(char *str, t_tkn *tkn, t_label **tail,
														t_arg_type arg_type);
t_arg			*add_arg(char *str, t_arg_type type);
char			*add_string(char *str, t_tkn *tkn);

void			tkn_fill(char *str, t_tkn *tkn, t_label **tail,
																u_int8_t flag);
u_int8_t		tkn_scroll(t_pc *pc, t_tkn *tkn);
void			scroll_n(t_pc *pc, u_int16_t n);
void			split_in_tkns(int fd, t_tkn **tkn, t_label **label);
u_int8_t		check_prev_str(t_tkn *tkn, u_int8_t flag);

u_int32_t		len_command(t_tkn *tkn);

void			replace_label(t_label *head);

char			*tkn_strcat(char *dst, t_tkn *tkn, u_int32_t max_len);
t_tkn			*find_tkn(t_tkn *head, t_tkn_type type);

void			tkn_error(char *error, t_tkn *tkn, _Bool warning);

_Bool			is_special_char(char c, char *specials);

_Bool			find_label(t_label **head, t_label *label_arg);

void			tkn_sequence(t_tkn *tkn, t_tkn_sec	*check_list);

void			commands_print(int fd, t_tkn *tkn);

void			header_print(int fd, t_header *header);
void			this_label(t_tkn *tkn, t_tkn_sec *check_list);
void			this_argument(t_tkn *tkn, t_tkn_sec *check_list);
void			this_name(t_tkn *tkn, t_tkn_sec *check_list);
void			this_comment_newline(t_tkn *tkn, t_tkn_sec *check_list);
void			this_comment_prog(t_tkn *tkn, t_tkn_sec *check_list);
void			test_command(t_tkn *tkn);
void			make_headers(t_header *header, t_tkn *tkn);

#endif