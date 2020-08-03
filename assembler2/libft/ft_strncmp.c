/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umoff <umoff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 14:10:40 by umoff             #+#    #+#             */
/*   Updated: 2020/07/02 13:46:56 by umoff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char c1;
	unsigned char c2;

	if (n == 0)
		return (0);
	c1 = (unsigned char)*s1;
	c2 = (unsigned char)*s2;
	while ((n > 1 && (c1 || c2)) && (!(c1 - c2)))
	{
		--n;
		++s1;
		++s2;
		c1 = (unsigned char)*s1;
		c2 = (unsigned char)*s2;
	}
	if ((c1 < c2) && ((c1 == '\0') || (c2 != '\0')))
		return (c1 - c2);
	else if ((c1 > c2) && ((c2 == '\0') || (c1 != '\0')))
		return (c1 - c2);
	else
		return (0);
}
