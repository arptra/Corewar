/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 21:02:38 by student           #+#    #+#             */
/*   Updated: 2020/07/30 21:02:45 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/parse.h"

void	live(t_vm *vm)
{
	int player_num;

	vm->car->move += 1; //move on 1 byte from op code to args
	player_num = get_arg(vm, 1);
	vm->car->move += vm->car->args_size->arg_1;
	vm->car->last_live = vm->cycle;
	vm->lives++;
	if (player_num <= -1 && player_num >= -vm->players_num)
	{
		vm->last_live = get_player(vm, -player_num);
		if (vm->d_mod == 1)
			printf("Player %d (%s) is said to be alive\n", vm->last_live->cnum, vm->last_live->cn);
	}
	if (vm->d_mod == 4)
		printf("P\t%d | live %d\n", vm->car->num, player_num);
}
