/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umoff <umoff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 14:08:36 by umoff             #+#    #+#             */
/*   Updated: 2020/07/02 13:44:38 by umoff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_sqrt(int num, _Bool precision)
{
	int root;

	if (num < 0)
		return (-1);
	if (!num)
		return (0);
	root = 1;
	while (root < num / root && (root + 1) <= num / (root + 1))
		++root;
	if (root * root == num)
		return (root);
	if (precision)
		return (-1);
	return (root);
}
