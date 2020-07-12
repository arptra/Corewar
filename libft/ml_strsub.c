/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umoff <umoff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 14:12:29 by umoff             #+#    #+#             */
/*   Updated: 2020/07/02 13:49:51 by umoff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ml_strsub(const char *s, unsigned int start, size_t len,
															u_int32_t lst_num)
{
	char *substr;

	if (!s || !(substr = ml_strnew(len, lst_num)))
		return (NULL);
	substr = ft_strncpy(substr, s + start, len);
	return (substr);
}
