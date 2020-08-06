/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 00:22:23 by gemerald          #+#    #+#             */
/*   Updated: 2019/09/13 00:46:54 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lst_free(t_list **alst)
{
	t_list *tmp;
	t_list *next_tmp;

	tmp = *alst;
	while (tmp)
	{
		next_tmp = tmp->next;
		free(&(tmp->content));
		free(&(tmp->content_size));
		free(tmp);
		tmp = next_tmp;
	}
	*alst = NULL;
}
