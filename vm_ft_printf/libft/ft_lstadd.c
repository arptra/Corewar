/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 19:12:52 by gemerald          #+#    #+#             */
/*   Updated: 2019/09/12 23:22:46 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstadd(t_list **alst, t_list *new)
{
	t_list *tmp;

	tmp = new;
	if (tmp)
	{
		tmp->next = *alst;
		*alst = tmp;
	}
	else
		*alst = tmp;
}
