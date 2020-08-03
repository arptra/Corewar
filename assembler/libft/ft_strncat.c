/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umoff <umoff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 14:10:35 by umoff             #+#    #+#             */
/*   Updated: 2020/07/02 13:46:48 by umoff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strncat(char *dest, const char *src, size_t nb)
{
	size_t i;

	i = 0;
	while (*dest)
	{
		++dest;
		++i;
	}
	while (*src && nb > 0)
	{
		*dest = *src;
		++src;
		++dest;
		++i;
		--nb;
	}
	*dest = '\0';
	return (dest - i);
}
