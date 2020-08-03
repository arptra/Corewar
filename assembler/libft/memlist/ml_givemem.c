/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_givemem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umoff <umoff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 14:12:17 by umoff             #+#    #+#             */
/*   Updated: 2020/07/02 13:33:02 by umoff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "blackbox_memlist.h"
#include "libft.h"

t_ml	*ml_bb_givemem(t_ml_lists *lst, u_int32_t list_num)
{
	while (lst && lst->list_num != list_num)
		lst = lst->next;
	if (!lst)
		go_exit("COMPILE ERROR: you want find t_ml list in memory group what \
does not exist");
	return (lst->list);
}
