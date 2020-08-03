/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_general.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umoff <umoff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 13:42:26 by umoff             #+#    #+#             */
/*   Updated: 2020/07/02 13:32:59 by umoff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "blackbox_memlist.h"
#include "libft.h"

void		*ml_malloc(size_t size, u_int32_t list_num)
{
	void *data;

	if (!(data = malloc(size)))
	{
		ml_static_lists(NULL, ML_CLEARLIST, list_num);
		return (NULL);
	}
	ml_static_lists(data, ML_MALLOC, list_num);
	return (data);
}

void		ml_free(void *ptr, u_int32_t list_num)
{
	ml_static_lists(ptr, ML_DELELEM, list_num);
}

void		ml_free_list(u_int32_t list_num)
{
	ml_static_lists(NULL, ML_CLEARLIST, list_num);
}

void		ml_free_all(void)
{
	ml_static_lists(NULL, ML_CLEARALL, 0);
}

t_ml		*ml_givemem(u_int32_t list_num)
{
	return (ml_static_lists(NULL, ML_GIVEMEM, list_num));
}
