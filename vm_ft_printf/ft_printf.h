/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 22:20:02 by gemerald          #+#    #+#             */
/*   Updated: 2020/01/18 20:25:36 by bgerda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "libft/libft.h"
# include <stdint.h>

# define BUFF 17000

union
{
	double				dl;
	uint64_t			dw;
}						u_d;

union
{
	long double			ldl;
	uint64_t			ldw;
}						u_ld;

typedef struct			s_double
{
	char				sp;
	int					fd;
	int					power;
	int					pow;
	int					counter;
	int					shift;
	int					lshift;
	int					f_flag;
	int					w_flag;
	int					s;
	uint16_t			e;
	unsigned long long	m;
}						t_double;

typedef struct			s_num
{
	char				num1[BUFF];
	char				num2[BUFF];
	char				num3[BUFF];
	char				num4[BUFF];
	int					len;
	int					precision;
	int					grate;
}						t_num;

typedef struct			s_utf
{
	char				mask;
	char				lead;
	uint32_t			beg;
	uint32_t			end;
	int					bits_stored;
}						t_utf;

typedef struct			s_upload
{
	unsigned long long	nbr;
	int					base;
	int					len;
	int					fd;
	char				sp;
}						t_upload;

int						smul(const char *a, char *c, int sym, int size);
void					get_mod(int size, char *c, char *a);
void					ft_add(char *a, char *b, char *c);
void					fill_zeros(char *a, char *b, char *tmp);
void					get_double(double num, t_double **var);
int						print_double(t_double var, int flags[]);
char					*rounding(char *num1, char *num2, char *res, int prec);
void					print_fpart(char *str, int i, int prec, int fd);
void					print_wpart(char *str, int fd);
void					sel_wpart(t_double var, t_num num);
int						preoutput2(t_double *var, t_num *num);
void					output(t_double var, t_num num);
void					add_aux(char *num1, char *num2, int counter, char *dig);
void					mod_aux(int counter, char *num1, char *dig, int *flag);
void					pow_add(t_double *var, t_num *num);
int						preoutput(t_double *var, t_num *num);
void					print_eg(t_double var, t_num num, int len, char sign);
void					pos_pow(t_num *num);
void					neg_pow(t_num *num, int len);
int						output_e(t_double var, t_num num);
int						print_g_pos(t_double var, t_num num);
int						print_g_neg(t_double var, t_num num,
										int len1, int len2);
int						output_g(t_double var, t_num num);
void					init(t_double *var, t_num *num, int flags[]);
void					sign_exp_ld(long double x, t_double **num);
void					get_ldouble(long double num, t_double **var);
void					uputchar_fd(char c, int fd, int r);
char					*to_utf8(const uint32_t cp);
int						codepoint_len(const uint32_t cp);
void					init_nbr(t_double *var, long double nbr,
														int flags[], char sp);
int						voyage(char *str, va_list *factor, int *jindex, int fd);
int						print_int(va_list *factor, char sp, int flags[]);
int						print_float(va_list *factor, char sp, int flags[]);
int						print_str(va_list *factor, char sp, int flags[]);
int						print_itoa(unsigned long long int n, int base,
														char sp, int fd);
int						nbr_len(unsigned long long nbr, int base);
unsigned long long int	unsigned_arg(va_list *factor, int flags[]);
long long int			signed_arg(va_list *factor, int flags[]);
void					kill_wide_di(long long int *nbr, int flags[]);
void					kill_wide_o(unsigned long long int *nbr, int flags[]);
void					flags_di(long long int *nbr, int flags[], int *i);
void					to_side_di(int wide, char field, int *i, int fd);
void					to_side_o(int wide, char field, int *i, int fd);
void					flags_u(unsigned long long int *nbr, int flags[], \
																	int *i);
void					flags_o(unsigned long long int *nbr, int flags[], \
																int *i);
void					kill_wide(unsigned long long int *nbr, int flags[]);
void					to_side_u(int wide, char field, int *i, int fd);
void					only_wide_di_next(long long int *nbr, \
											int flags[], int *i, int wide);
void					only_wide_u_next(unsigned long long int *nbr, \
											int flags[], int *i, int base);
void					only_wide_u(unsigned long long int *nbr, \
											int flags[], int *i, int base);
int						print_u(va_list *factor, int flags[], char sp);
int						print_trash(char sp, int flags[]);
int						voyager_wp(char *str, int flags[], va_list *factor);
void					move_wild(int flags[], int *to_wp);
int						voyager_size(char *str, int flags[]);
int						find_type(va_list *factor, char sp, int flags[]);
int						print_str(va_list *factor, char sp, int flags[]);
int						print_char(va_list *factor, char sp, int flags[]);
int						print_o(va_list *factor, int flags[], char sp);
long double				signed_float(va_list *factor, int flags[]);
void					nbr_double_len(long double nbr, int flags[]);
void					kill_wide_f(long double *nbr, int flags[]);
void					flags_f(int flags[], int *i);
int						ft_printf(char *str, ...);
int						ft_dprintf(int fd, char *str, ...);

#endif
