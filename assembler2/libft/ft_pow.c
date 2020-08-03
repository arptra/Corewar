/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umoff <umoff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 14:07:05 by umoff             #+#    #+#             */
/*   Updated: 2020/07/02 13:42:24 by umoff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

double	ft_pow(double num, long long power)
{
	double	res;
	_Bool	flg;

	res = 1.;
	flg = 1;
	power < 0 ? flg = 0 : flg;
	while (power)
	{
		if (!(power % 2))
		{
			num *= num;
			power /= 2;
		}
		else
		{
			power < 0 ? ++power : --power;
			res *= num;
		}
	}
	return (!flg ? 1. / res : res);
}
