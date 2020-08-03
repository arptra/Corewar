/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umoff <umoff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 14:03:43 by umoff             #+#    #+#             */
/*   Updated: 2020/07/02 13:40:49 by umoff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *curr;

	if (alst && *alst && del)
	{
		curr = *alst;
		while (curr)
		{
			*alst = (*alst)->next;
			ft_lstdelone(&curr, del);
			curr = *alst;
		}
	}
}
