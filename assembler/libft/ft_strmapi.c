/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umoff <umoff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 14:10:30 by umoff             #+#    #+#             */
/*   Updated: 2020/07/02 13:46:46 by umoff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*new_str;
	char			*ptr2new;

	if (!s || !f || !(new_str = ft_strnew(ft_strlen(s))))
		return (NULL);
	i = 0;
	ptr2new = new_str;
	while (s[i])
	{
		*ptr2new++ = (*f)(i, s[i]);
		++i;
	}
	return (new_str);
}
