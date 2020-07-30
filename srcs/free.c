/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 21:06:06 by student           #+#    #+#             */
/*   Updated: 2020/07/30 21:06:09 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/parse.h"

void	free_car(t_carriage **car)
{
	free((*car)->a_s);
	free((*car)->a_t);
	free(*car);
}

void 	free_player(t_file_info **player)
{
	t_file_info *next;
	t_file_info *cur;

	cur = *player;
	while (cur)
	{
		next = cur->next;
		free(cur->cn);
		free(cur->cc);
		free(cur);
		cur = next;
	}
}

void	ft_free_vm(t_vm **vm)
{
	t_carriage	*next;
	t_carriage	*car;
	t_file_info	*player;

	if ((*vm)->car)
	{
		car = (*vm)->car;
		while (car) {
			next = car->next;
			free_car(&car);
			car = next;
		}
	}
	if ((*vm)->players)
	{
		player = (*vm)->players;
		free_player(&player);
	}
	free((*vm)->arena);
	free(*vm);
}
