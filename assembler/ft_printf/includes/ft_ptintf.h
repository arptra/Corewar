/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptintf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umoff <umoff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 13:43:53 by umoff             #+#    #+#             */
/*   Updated: 2020/07/02 13:23:48 by umoff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PTINTF_H
# define FT_PTINTF_H
# include <stdarg.h>
# include <stdint.h>
# define BUFF_SIZE  60

# define M_MINUS 1
# define M_PLUS 2
# define M_SHARP 4
# define M_ZERO 8
# define M_SPACE 16
# define M_B 32
# define M_PRECISION_NOT_ADDED 64
# define M_ZERO_CHAR 128

# define M_HH 1
# define M_H 2
# define M_L 4
# define M_LL 8
# define M_UPPER_L 16

# define NON_FORMAT 0
# define FORMAT 1
# define LAST 2

# define LOG10_2 0.30103

# include "libft.h"

typedef struct		s_prsng
{
	char			flags;
	size_t			field;
	int				prec;
	unsigned char	mdfirs;
	char			type;
	size_t			counter;
	char			buff[BUFF_SIZE + 1];
	va_list			ap;
	char			*str_spf;
}					t_prsng;

typedef union		u_un
{
	int					i;
	unsigned int		ui;
	long				l;
	unsigned long		ul;
	short				sh;
	unsigned short		ush;
	long long			ll;
	unsigned long long	ull;
	char				c;
	unsigned char		uc;
	double				db;
	long double			ldb;
	char				*cptr;
}					t_un;

typedef struct		s_mkfld
{
	size_t	lennum;
	size_t	len;
	size_t	len_empty_field;
	t_un	nmbr;
	int		base;
	char	*str;
}					t_mkfld;

int					ft_printf(const char *format, ...);
int					ft_sprintf(char *str, char *format, ...);

int					parsing(char **format, t_prsng *tools);
void				to_buff(char *str, t_prsng *tools, t_mkfld *field);
void				add_str_to_buff(char **format, t_prsng *tools);

void				set_flags(t_mkfld *field, t_prsng *tools);

_Bool				set_buff(t_mkfld *fld, t_prsng *tls);
_Bool				set_buff_float(t_mkfld *fld, t_prsng *tls);
void				buffer_managment(t_prsng *tools, char *str, int len,
										int type_output);

void				zeroing_tools(t_prsng *tools, _Bool zeroing_counter);

int					organozation_by_flags_to_buff(t_prsng *tools);

size_t				count_lennum(t_mkfld *field, t_prsng *tools);
int					define_base(t_prsng *tools);
int					define_flaglen(t_mkfld *fld, t_prsng *tls);

unsigned long long	reverse_if_negative(t_un *number, t_prsng *tools);

char				*itoa_base_union(t_prsng *tools, t_mkfld *field, char *str);

_Bool				is_signed(char c);
_Bool				is_typeflag(char c);
_Bool				is_ddioouuxx(char c);
_Bool				is_aaeeffgg(char c);
_Bool				is_csp(char c);
_Bool				is_signflag(char c);
_Bool				is_modifiers(char c);
_Bool				is_flag(char c);

int					which_sign(t_un *number, t_prsng *tools);

char				*print_double(t_prsng *tools, t_mkfld *fld, double number);
char				*print_long_double(t_prsng *tools, t_mkfld *fld,
								long double number);
char				*get_binary(uint64_t *num, size_t bit_size, t_mkfld *fld,
						const char type);

void				fill_union_diouxx(t_mkfld *field, t_prsng *tools);
_Bool				fill_union_csp(t_mkfld *field, t_prsng *tools);
void				fill_union_aaeeffgg(t_mkfld *field, t_prsng *tools);
void				len_counting_diouxxcsp(t_prsng *tools, t_mkfld *field);
void				zeroing_mkfield(t_mkfld *fld);

void				parsing_flags(char **format, t_prsng *tools);
void				parsing_modifiers(char **format, t_prsng *tools);
void				parsing_field(char **format, t_prsng *tools);
void				parsing_precision(char **format, t_prsng *tools);
void				parsing_typeflag(char **format, t_prsng *tools);

void				diouxxcsp_lennum(t_prsng *tools, t_mkfld *field);
void				aaeeffgg_lennum_len(t_prsng *tools, t_mkfld *field);

void				get_binaryd_by_type(t_prsng *tools, t_mkfld *fld);

void				str_tolower(char *str);

#endif
