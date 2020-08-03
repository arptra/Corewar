/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_create.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umoff <umoff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 13:42:14 by umoff             #+#    #+#             */
/*   Updated: 2020/07/02 13:32:40 by umoff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "blackbox_memlist.h"

t_ml_lists	*create_ml_lst_elem(u_int32_t list_num)
{
	t_ml_lists	*new;

	if (!(new = (t_ml_lists*)malloc(sizeof(t_ml_lists))))
		go_exit("ERROR: can't alloc memory");
	new->list_num = list_num;
	new->list = NULL;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_ml_lists	*add_ml_list(u_int32_t list_num, t_ml_lists **cur,
															t_ml_lists **head)
{
	t_ml_lists	*new;

	new = create_ml_lst_elem(list_num);
	if (!*cur)
		*cur = new;
	else if ((*cur)->list_num < list_num)
	{
		(*cur)->next = new;
		new->prev = *cur;
	}
	else
	{
		new->prev = (*cur)->prev;
		new->next = *cur;
		if ((*cur)->prev)
			(*cur)->prev->next = new;
		(*cur)->prev = new;
	}
	if (!new->prev)
		*head = new;
	return (new);
}

t_ml		*ml_create(void *ptr)
{
	t_ml *new;

	new = NULL;
	if (!(new = (t_ml*)malloc(sizeof(t_ml))))
		return (NULL);
	new->data = ptr;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

_Bool		ml_push_front(t_ml_lists **lst, t_ml *new)
{
	t_ml **head;

	head = &(*lst)->list;
	if (!new)
	{
		ml_clear_lst(lst, NULL);
		return (1);
	}
	if (head && *head)
	{
		new->next = *head;
		(*head)->prev = new;
	}
	*head = new;
	return (1);
}
