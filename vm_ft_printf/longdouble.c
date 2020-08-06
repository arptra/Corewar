/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   longdouble.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgerda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 14:29:23 by bgerda            #+#    #+#             */
/*   Updated: 2020/01/18 19:59:03 by bgerda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	get_double(double num, t_double **var)
{
	u_d.dl = num;
	(*var)->counter = 51;
	(*var)->shift = 1023;
	(*var)->s = (u_d.dw >> 63) ? -1 : 1;
	(*var)->e = (u_d.dw >> 52) & 0x7FF;
	(*var)->m = (*var)->e ? (u_d.dw & 0xFFFFFFFFFFFFF) | 0x10000000000000 :
						(u_d.dw & 0xFFFFFFFFFFFFF) << 1;
	(*var)->pow = (*var)->e - (*var)->shift;
	(*var)->lshift = 0;
}

void	sign_exp_ld(long double x, t_double **num)
{
	int				i;
	int				j;
	int				k;
	unsigned char	*gg;
	unsigned char	tmp;

	gg = (unsigned char *)&x;
	k = 0;
	i = -1;
	while (++i < 10)
	{
		tmp = *(gg++);
		j = -1;
		while (++j < 8)
		{
			if (i >= 8 && (tmp & 1))
				(*num)->e |= (1 << k++);
			else if (i >= 8 && !(tmp & 1))
				(*num)->e &= ~(1 << k++);
			tmp >>= 1;
		}
	}
	(*num)->s = ((*num)->e >> 15) ? -1 : 1;
	(*num)->e = (*num)->e & 0x7fff;
}

void	get_ldouble(long double num, t_double **var)
{
	(*var)->counter = 63;
	(*var)->shift = 16382;
	sign_exp_ld(num, var);
	u_ld.ldl = num;
	(*var)->m = u_ld.ldw & 0xFFFFFFFFFFFFFFFF;
	(*var)->pow = (*var)->e - (*var)->shift - 1;
	(*var)->lshift = 1;
}

void	fill_zeros(char *a, char *b, char *tmp)
{
	int	len1;
	int	len2;
	int	i;

	i = -1;
	len1 = ft_strlen(a);
	len2 = ft_strlen(b);
	if (len1 > len2)
	{
		ft_strncpy(tmp, b, len2 + 1);
		while (++i < len1 - len2)
			b[i] = '0';
		ft_strncpy(&b[i], tmp, ft_strlen(tmp) + 1);
		ft_strclr(tmp);
	}
	else
		fill_zeros(b, a, tmp);
}

void	init_nbr(t_double *var, long double nbr, int flags[], char sp)
{
	var->sp = sp;
	if (flags[8] == 111)
		get_ldouble(nbr, &var);
	else
		get_double((double)nbr, &var);
}
