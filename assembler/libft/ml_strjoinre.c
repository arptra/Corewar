/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_strjoinre.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umoff <umoff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 14:12:48 by umoff             #+#    #+#             */
/*   Updated: 2020/07/02 13:49:27 by umoff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ml_strjoinre(char **s1, char const *s2, u_int32_t lst_num)
{
	char *new;

	if (!(new = ml_strjoin(*s1, s2, lst_num)))
		return (NULL);
	free(*s1);
	*s1 = new;
	return (*s1);
}
