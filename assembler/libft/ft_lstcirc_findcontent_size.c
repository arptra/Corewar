/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcirc_findcontent_size.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umoff <umoff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 14:03:31 by umoff             #+#    #+#             */
/*   Updated: 2020/07/02 13:40:42 by umoff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_lstcirc_findcontent_size(t_list **lst, size_t content_size)
{
	t_list *cur;

	if (!lst || !*lst)
		return (0);
	if ((*lst)->content_size == content_size)
		return (1);
	cur = (*lst)->next;
	while (cur != *lst && cur->content_size != content_size)
		cur = cur->next;
	if (cur == *lst)
		return (0);
	return ((*lst = cur) == cur);
}
