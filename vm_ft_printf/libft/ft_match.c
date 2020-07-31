/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_match.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 19:31:13 by gemerald          #+#    #+#             */
/*   Updated: 2019/09/12 20:41:37 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_match(char *s1, char *s2, char point)
{
	if ((*s1 == '\0') && (*s2 == point))
		return (ft_match(s1, s2 + 1, point));
	if ((*s1 != '\0') && (*s2 == point))
		return (ft_match(s1 + 1, s2, point) || (ft_match(s1, s2 + 1, point)));
	if ((*s1 == *s2) && (*s1 != '\0') && (*s1 != point))
		return (ft_match(s1 + 1, s2 + 1, point));
	if ((*s1 == *s2) && (*s1 == '\0'))
		return (1);
	if ((*s1 != *s2) && (*s2 != point))
		return (0);
	return (0);
}
