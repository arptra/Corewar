/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 21:07:11 by student           #+#    #+#             */
/*   Updated: 2020/07/30 21:07:13 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/parse.h"

void			ft_swap_players(t_file_info *temp1,
								t_file_info *temp2,
								t_vm *vm)
{
	t_file_info		*temp3;

	if (!(temp3 = (t_file_info*)ft_memalloc(sizeof(t_file_info))))
		ft_error(-1, vm);
	temp3->cn = temp1->cn;
	temp3->cs = temp1->cs;
	temp3->cc = temp1->cc;
	temp3->cnum = temp1->cnum;
	temp3->fd = temp1->fd;
	temp1->cn = temp2->cn;
	temp1->cs = temp2->cs;
	temp1->cc = temp2->cc;
	temp1->cnum = temp2->cnum;
	temp1->fd = temp2->fd;
	temp2->cn = temp3->cn;
	temp2->cs = temp3->cs;
	temp2->cc = temp3->cc;
	temp2->cnum = temp3->cnum;
	temp2->fd = temp3->fd;
	free(temp3);
}
void			ft_sort_players(t_vm *vm)
{
	t_file_info		*temp1;
	t_file_info		*temp2;
	int				flag;

	while (1)
	{
		temp1 = vm->players;
		flag = 1;
		while (temp1->next)
		{
			temp2 = temp1->next;
			if (temp1->cnum > temp2->cnum)
			{
				ft_swap_players(temp1, temp2, vm);
				flag = 0;
			}
			else if (temp1->cnum == temp2->cnum)
				ft_error(7, vm);
			temp1 = temp1->next;
		}
		if (flag)
			return ;
	}
}

t_vm			*ft_players(t_vm *vm, int players_num)
{
	t_file_info		*temp1;
	int				cnt;

	temp1 = vm->players;
	cnt = 0;
	while (temp1)
	{
		if (!(temp1->cnum))
		{
			temp1->cnum = ft_get_current_num(temp1, cnt);
			cnt = temp1->cnum + 1;
		}
		if (temp1->cnum > players_num)
			ft_error(8, vm);
		temp1->players_num = players_num;
		temp1 = temp1->next;
	}
	ft_sort_players(vm);
	return (vm);
}

t_vm			*ft_parse_flags(int argc, char **argv, t_vm *vm)
{
	if (--(vm->nbr_cycles) && ft_strequ(argv[1], "-dump"))
	{
		if ((vm->nbr_cycles = ft_atoi(argv[2])) < 0)
			ft_error(9, vm);
		vm->players_num = vm->players_num - 2;
		vm->itrtr += 2;
	}
	if (ft_strequ(argv[vm->itrtr+1], "-i") && ++vm->itrtr && --vm->players_num)
		vm->flag_vis = 1;
	vm->debug = -1;
	if (ft_strequ(argv[vm->itrtr+1], "-d") && (vm->players_num -= 2))
		if ((vm->itrtr += 2) >= argc ||
			((vm->d_mod = ft_atoi(argv[vm->itrtr])) != 0 &&
			vm->d_mod != 1 && vm->d_mod != 2 && vm->d_mod != 4 &&
			vm->d_mod != 8 && vm->d_mod != 16))
			ft_error(13, vm);
	return (vm);
}

t_vm			*parse_args(int argc, char **argv, t_vm *vm)
{
	int				player_num;
	t_file_info		*temp;

	vm->players_num = argc - 1;
	vm = ft_parse_flags(argc, argv, vm);
	while (++vm->itrtr < argc)
	{
		if (ft_strequ(argv[vm->itrtr], "-n"))
			if ( ++vm->itrtr >= argc
				|| (player_num = ft_atoi(argv[vm->itrtr])) <= 0
				|| player_num > (vm->players_num -= 2) || ++vm->itrtr >= argc
				)
				ft_error(10, vm);
		if ((vm->players == NULL) &&
			(vm->players = parse_player(argv[vm->itrtr], vm)))
			temp = vm->players;
		else if ((temp->next = parse_player(argv[vm->itrtr], vm)))
			temp = temp->next;
	}
	if (vm->players_num > MAX_PLAYERS)
		ft_error(11, vm);
	if (vm->debug > 0)
		vm->players_num = 1;
	return (ft_players(vm, vm->players_num));
}
