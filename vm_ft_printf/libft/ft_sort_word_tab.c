/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_word_tab.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 18:58:06 by gemerald          #+#    #+#             */
/*   Updated: 2019/09/12 19:39:11 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_sort_word_tab(char **arr)
{
	int		y;
	int		eql;
	char	*swap;

	eql = 1;
	while (eql > 0)
	{
		eql = 0;
		y = 0;
		while (arr[y + 1] != NULL)
		{
			if (ft_strcmp(arr[y], arr[y + 1]) > 0)
			{
				swap = arr[y + 1];
				arr[y + 1] = arr[y];
				arr[y] = swap;
				eql++;
			}
			y++;
		}
	}
}
