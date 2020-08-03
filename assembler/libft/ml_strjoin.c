/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umoff <umoff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 14:13:13 by umoff             #+#    #+#             */
/*   Updated: 2020/07/02 13:49:24 by umoff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ml_strjoin(const char *s1, const char *s2, u_int32_t lst_num)
{
	char	*new_str;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	else if (s1 == NULL)
		return (ml_strdup(s2, lst_num));
	else if (s2 == NULL)
		return (ml_strdup(s1, lst_num));
	new_str = ml_strnew(ft_strlen(s1) + ft_strlen(s2), 0);
	if (!new_str)
		return (NULL);
	new_str = ft_strcat(new_str, s1);
	new_str = ft_strcat(new_str, s2);
	return (new_str);
}
