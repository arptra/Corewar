/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umoff <umoff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 13:41:55 by umoff             #+#    #+#             */
/*   Updated: 2020/07/02 13:49:37 by umoff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "memlist.h"

char	*ml_strndup(const char *s1, size_t n, u_int32_t lst_num)
{
	char	*str;
	size_t	len;

	len = ft_strlen(s1);
	if (len < n)
		str = (char*)ml_malloc(sizeof(str) * (len + 1), lst_num);
	else
		str = (char*)ml_malloc(sizeof(str) * (n + 1), lst_num);
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, s1, n + 1);
	return (str);
}
