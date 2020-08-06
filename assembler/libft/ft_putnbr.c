/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umoff <umoff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 14:07:44 by umoff             #+#    #+#             */
/*   Updated: 2020/07/02 13:43:28 by umoff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int n)
{
	long long new;

	new = (long long)n;
	if (new < 0)
	{
		ft_putchar('-');
		new = -new;
	}
	if (new < 10)
	{
		ft_putchar(new + '0');
	}
	else
	{
		ft_putnbr(new / 10);
		ft_putnbr(new % 10);
	}
}
