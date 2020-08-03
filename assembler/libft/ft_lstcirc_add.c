/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcirc_add.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umoff <umoff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 14:03:15 by umoff             #+#    #+#             */
/*   Updated: 2020/07/02 13:40:25 by umoff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstcirc_add(t_list **cur, char const *content, size_t content_size)
{
	t_list *new;

	if (!cur || !(new = ft_lstcirc_strnew(content, content_size)))
		return (NULL);
	if (!*cur)
		*cur = new;
	else
	{
		new->next = (*cur)->next;
		(*cur)->next = new;
	}
	return (new);
}
