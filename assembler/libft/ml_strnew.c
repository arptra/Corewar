/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umoff <umoff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 14:12:42 by umoff             #+#    #+#             */
/*   Updated: 2020/07/02 13:49:44 by umoff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ml_strnew(size_t size, u_int32_t lst_num)
{
	char *new_str;

	if (size + 1 == 0)
		return (NULL);
	new_str = (char *)ml_memalloc(size + 1, lst_num);
	return (new_str);
}
