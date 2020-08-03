/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umoff <umoff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 14:13:27 by umoff             #+#    #+#             */
/*   Updated: 2020/07/02 13:49:19 by umoff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "memlist.h"

void	*ml_memalloc(size_t size, u_int32_t lst_num)
{
	void *new_mem;

	if (!(new_mem = ml_malloc(size, lst_num)))
		return (NULL);
	return (ft_memset(new_mem, 0, size));
}
