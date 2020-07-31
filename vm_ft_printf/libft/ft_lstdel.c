/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 19:14:49 by gemerald          #+#    #+#             */
/*   Updated: 2019/09/13 00:23:38 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *tmp;
	t_list *next_tmp;

	tmp = *alst;
	while (tmp)
	{
		next_tmp = tmp->next;
		del(tmp->content, tmp->content_size);
		free(tmp);
		tmp = next_tmp;
	}
	*alst = NULL;
}
