/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umoff <umoff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 14:04:59 by umoff             #+#    #+#             */
/*   Updated: 2020/07/02 13:41:00 by umoff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static void	delnode(void *data, size_t size)
{
	if (data)
	{
		free(data);
		data = NULL;
		size = 0;
	}
}

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *new_head;
	t_list *node;
	t_list *curr;

	if (lst && f)
	{
		new_head = NULL;
		curr = lst;
		while (curr)
		{
			if (!(node = (*f)(curr)))
			{
				ft_lstdel(&new_head, delnode);
				return (new_head);
			}
			ft_lstpush(&new_head, node);
			curr = curr->next;
		}
		return (new_head);
	}
	return (NULL);
}
