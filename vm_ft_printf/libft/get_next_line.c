/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 10:39:21 by gemerald          #+#    #+#             */
/*   Updated: 2019/09/21 22:40:59 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			find_n_len(char *buf)
{
	size_t i;

	i = 0;
	while ((buf[i]) && (buf[i] != '\n'))
		i++;
	return (i);
}

int			get_push(char **asylum, char **line)
{
	size_t	len;
	char	*tmp;

	len = find_n_len(*asylum);
	if ((*asylum)[len] == '\0')
	{
		*line = ft_strdup(*asylum);
		ft_strdel(&(*asylum));
	}
	else if ((*asylum)[len] == '\n')
	{
		*line = ft_strsub(*asylum, 0, len);
		tmp = ft_strdup(*asylum + len + 1);
		free(*asylum);
		*asylum = tmp;
		if (*asylum == NULL)
			ft_strdel(&(*asylum));
	}
	return (1);
}

int			get_next_line(const int fd, char **line)
{
	static char		*asylum[10240];
	char			buf[BUFF_SIZE + 1];
	char			*joint;
	int				ret;

	if ((fd < 0) || !line || (read(fd, buf, 0) < 0))
		return (-1);
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		if (!asylum[fd])
			asylum[fd] = ft_strnew(1);
		joint = ft_strjoin(asylum[fd], buf);
		free(asylum[fd]);
		asylum[fd] = joint;
		if ((ft_strchr(asylum[fd], '\n')))
			break ;
	}
	if (ret < 0)
		return (-1);
	if ((!asylum[fd] || !asylum[fd][0]) && ret == 0)
		return (0);
	return (get_push(&asylum[fd], line));
}
