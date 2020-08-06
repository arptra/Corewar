/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umoff <umoff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 14:07:33 by umoff             #+#    #+#             */
/*   Updated: 2020/07/02 13:44:14 by umoff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long long new;

	new = (long long)n;
	if (new < 0)
	{
		ft_putchar_fd('-', fd);
		new = -new;
	}
	if (new < 10)
	{
		ft_putchar_fd(new + '0', fd);
	}
	else
	{
		ft_putnbr_fd(new / 10, fd);
		ft_putnbr_fd(new % 10, fd);
	}
}
