/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 19:25:40 by gemerald          #+#    #+#             */
/*   Updated: 2019/09/12 22:52:58 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	size_t	i;
	void	*area;

	i = 0;
	if (!(area = (void *)malloc(size)))
		return (NULL);
	while (i < size)
	{
		((char *)area)[i] = 0;
		i++;
	}
	return (area);
}
