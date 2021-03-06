/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parametrs_to_op_code.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 21:05:17 by student           #+#    #+#             */
/*   Updated: 2020/07/30 21:05:20 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/corewar.h"

int	next_gds(uint8_t byte)
{
	if (byte == 0x0a)
		return (2);
	else if (byte == 0x0b)
		return (2);
	else if (byte == 0x0c)
		return (2);
	else if (byte == 0x0d)
		return (4);
	else if (byte == 0x0e)
		return (2);
	else if (byte == 0x0f)
		return (2);
	else if (byte == 0x10)
		return (4);
	else
		return (0);
}

int	get_dir_size(uint8_t byte)
{
	if (byte == 0x01)
		return (4);
	else if (byte == 0x02)
		return (4);
	else if (byte == 0x03)
		return (4);
	else if (byte == 0x04)
		return (4);
	else if (byte == 0x05)
		return (4);
	else if (byte == 0x06)
		return (4);
	else if (byte == 0x07)
		return (4);
	else if (byte == 0x08)
		return (4);
	else if (byte == 0x09)
		return (2);
	else
		return (next_gds(byte));
}

int	next_cte(uint8_t byte)
{
	if (byte == 0x0a)
		return (25);
	else if (byte == 0x0b)
		return (25);
	else if (byte == 0x0c)
		return (800);
	else if (byte == 0x0d)
		return (10);
	else if (byte == 0x0e)
		return (50);
	else if (byte == 0x0f)
		return (1000);
	else if (byte == 0x10)
		return (2);
	return (0);
}

int	get_cycle_to_exec(uint8_t byte)
{
	if (byte == 0x01)
		return (10);
	else if (byte == 0x02)
		return (5);
	else if (byte == 0x03)
		return (5);
	else if (byte == 0x04)
		return (10);
	else if (byte == 0x05)
		return (10);
	else if (byte == 0x06)
		return (6);
	else if (byte == 0x07)
		return (6);
	else if (byte == 0x08)
		return (6);
	else if (byte == 0x09)
		return (20);
	else
		return (next_cte(byte));
}

int	type_exception(uint8_t byte)
{
	if (byte == 0x01 || byte == 0x09
		|| byte == 0x0c || byte == 0x0f)
		return (get_dir_size(byte));
	return (0);
}
