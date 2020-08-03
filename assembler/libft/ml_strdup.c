/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umoff <umoff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 14:13:20 by umoff             #+#    #+#             */
/*   Updated: 2020/07/02 13:49:21 by umoff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "memlist.h"

char	*ml_strdup(const char *src, u_int32_t lst_num)
{
	int		len;
	char	*new_str;

	new_str = NULL;
	len = ft_strlen(src);
	new_str = (char *)ml_malloc(sizeof(char) * (len + 1), lst_num);
	if (new_str == NULL)
		return (NULL);
	ft_strcpy(new_str, src);
	return (new_str);
}
