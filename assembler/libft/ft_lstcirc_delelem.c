/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcirc_delelem.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umoff <umoff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 14:03:24 by umoff             #+#    #+#             */
/*   Updated: 2020/07/02 13:40:38 by umoff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstcirc_delelem(t_list **del_elem)
{
	t_list *prev;

	if (!del_elem || !*del_elem)
		return (NULL);
	if ((*del_elem)->next == *del_elem)
	{
		if ((*del_elem)->content)
			free((*del_elem)->content);
		free(*del_elem);
		return (NULL);
	}
	prev = (*del_elem)->next;
	while (prev->next != (*del_elem))
		prev = prev->next;
	prev->next = (*del_elem)->next;
	if ((*del_elem)->content)
		free((*del_elem)->content);
	free(*del_elem);
	return (prev);
}
