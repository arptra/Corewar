/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_complex_string.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umoff <umoff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 13:53:54 by umoff             #+#    #+#             */
/*   Updated: 2020/07/02 13:39:28 by umoff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_is_complex_string(char *str, char delim)
{
	int i;

	i = 0;
	while (*str)
	{
		if (*str == delim)
		{
			i++;
			while (*str && *str == delim)
				str++;
		}
		if (*str)
			str++;
	}
	return (i);
}
