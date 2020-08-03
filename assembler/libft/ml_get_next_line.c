/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umoff <umoff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 13:41:48 by umoff             #+#    #+#             */
/*   Updated: 2020/07/02 13:49:11 by umoff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ml_get_next_line(const int fd, char **line, u_int32_t lst_num)
{
	char			buf[BF_SZ_GNL + 1];
	static t_gnl	*lst;
	char			*temp;
	ssize_t			b;

	if (fd < 0 || !line || (!find_fd(&lst, fd) && !(ad_fd(&lst, new_node(fd)))))
		return (-1);
	find_fd(&lst, fd);
	while (!(ft_strchr(lst->str, '\n')) && (b = read(fd, &buf, BF_SZ_GNL)) > 0)
	{
		buf[b] = '\0';
		temp = lst->str;
		lst->str = ft_strjoin(lst->str, buf);
		ft_strdel(&temp);
	}
	if (b == -1 || (!*(temp = lst->str) && free_node(&lst)))
		return (b == -1 ? -1 : 0);
	if (!(lst->lb = ft_strchr(lst->str, '\n')))
		*line = ml_strdup(lst->str, lst_num);
	else
		*line = ml_strsub(lst->str, 0, lst->lb - lst->str, lst_num);
	lst->str = ft_strsub(lst->str, (unsigned int)(ft_strlen(*line) + 1),
			ft_strlen(lst->str) - ft_strlen(*line));
	ft_strdel(&temp);
	return (1);
}
