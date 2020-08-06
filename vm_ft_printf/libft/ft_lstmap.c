/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 19:20:11 by gemerald          #+#    #+#             */
/*   Updated: 2019/09/13 00:35:49 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *first;
	t_list *mapped;

	first = NULL;
	if (lst && f)
	{
		if (!(first = ft_lstnew(NULL, 0)))
			return (NULL);
		if (!(first = f(lst)))
			return (NULL);
		mapped = first;
		while (lst->next)
		{
			lst = lst->next;
			if (!(mapped->next = f(lst)))
			{
				ft_lst_free(&first);
				return (NULL);
			}
			mapped = mapped->next;
		}
	}
	return (first);
}
