/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umoff <umoff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 14:10:46 by umoff             #+#    #+#             */
/*   Updated: 2020/07/02 13:47:03 by umoff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, size_t n)
{
	char	*str;
	size_t	len;

	len = ft_strlen(s1);
	if (len < n)
		str = (char*)malloc(sizeof(str) * (len + 1));
	else
		str = (char*)malloc(sizeof(str) * (n + 1));
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, s1, n + 1);
	return (str);
}
