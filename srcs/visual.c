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

void	print_add_player(t_vm *vm, const int player_id,
							const char *name, int address)
{
	uint8_t	*arena;
	int		codesize;

	ft_printf("p%c%d%c%d%c%s%c%d%c", SEP, vm->cycle, SEP, player_id,
		   SEP, name, SEP, address, SEP);
	codesize = get_player(vm, player_id)->cs;
	arena = &vm->arena[address];
	while (codesize)
	{
		print_byte_by_ptr(arena);
		arena++;
		codesize--;
	}
	ft_printf("\n");
}

void	print_add_carriage(t_vm *vm, int player_id, t_carriage *car)
{
	ft_printf("c%c%d%c%d%c%d%c%d\n", SEP, vm->cycle, SEP,
		   player_id, SEP, car->num, SEP, car->pc);
}

void	print_kill_carriage(t_vm *vm, t_carriage *car)
{
	ft_printf("k%c%d%c%d%c%d\n", SEP, vm->cycle, SEP,
		   car->p->cnum, SEP, car->num);
}
