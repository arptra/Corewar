/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umoff <umoff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 14:09:12 by umoff             #+#    #+#             */
/*   Updated: 2020/07/02 13:46:03 by umoff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_strcmp(const char *s1, const char *s2)
{
	unsigned char c1;
	unsigned char c2;

	c1 = (unsigned char)*s1;
	c2 = (unsigned char)*s2;
	while (!(c1 - c2) && (c1 || c2))
	{
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
