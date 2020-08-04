/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 21:08:53 by student           #+#    #+#             */
/*   Updated: 2020/07/30 21:08:55 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/corewar.h"

void	print_move_carriage(t_vm *vm, const int player_id, int offset)
{
	ft_printf("m%c%d%c%d%c%d%c%d\n", SEP, vm->cycle, SEP, player_id, SEP,
					vm->car->num, SEP, offset);
}

void	print_write_memory(t_vm *vm, int player_id, int address,
							int32_t reg_value)
{
	ft_printf("w%c%d%c%d%c%d%c%08X\n", SEP, vm->cycle, SEP, player_id,
					SEP, address, SEP, reg_value);
}

void	print_declare_winner(t_vm *vm)
{
	ft_printf("e%c%d%c%d\n", SEP, vm->cycle, SEP, vm->last_live->cnum);
}
