/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcirc_strnew.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umoff <umoff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 14:03:36 by umoff             #+#    #+#             */
/*   Updated: 2020/07/02 13:40:45 by umoff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstcirc_strnew(char const *content, size_t content_size)
{
	t_list *new;

	new = (t_list*)malloc(sizeof(t_list));
	if (new == NULL)
		return (NULL);
	if (content)
	{
		new->content = (void *)ft_strdup(content);
		if (!(new->content))
		{
			free(new);
			return (NULL);
		}
	}
	else
		new->content = NULL;
	new->content_size = content_size;
	new->next = new;
	return (new);
}
