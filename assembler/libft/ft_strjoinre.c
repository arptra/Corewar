/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinre.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umoff <umoff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 14:09:52 by umoff             #+#    #+#             */
/*   Updated: 2020/07/02 13:46:28 by umoff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoinre(char **s1, char const *s2)
{
	char *new;

	if (!(new = ft_strjoin(*s1, s2)))
		return (NULL);
	free(*s1);
	*s1 = new;
	return (*s1);
}
