/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stdin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 22:59:34 by gemerald          #+#    #+#             */
/*   Updated: 2019/09/23 20:45:34 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_char		*ft_create_elem(char c)
{
	t_char *tmp;

	if (!(tmp = (t_char *)malloc(sizeof(t_char))))
		return (NULL);
	tmp->next = NULL;
	tmp->c = c;
	return (tmp);
}

static void			ft_list_del(t_char **begin_list)
{
	t_char *link;
	t_char *f_link;

	link = *begin_list;
	while (link != NULL)
	{
		f_link = link->next;
		free(link);
		link = f_link;
	}
}

static void			ft_push_back(t_char **begin_list, char c)
{
	t_char *list;

	list = *begin_list;
	if (list != NULL)
	{
		while (list->next)
			list = list->next;
		if (!(list->next = ft_create_elem(c)))
			ft_list_del(&list);
	}
	else
	{
		if (!(*begin_list = ft_create_elem(c)))
			ft_list_del(begin_list);
	}
}

static char			*ft_concat(t_char **begin_list, int list_len)
{
	int			index;
	char		*str;
	t_char		*list;

	list = *begin_list;
	index = 0;
	if (!(str = (char *)malloc(sizeof(char) * list_len + 1)))
		return (NULL);
	while (index < list_len)
	{
		str[index] = list->c;
		list = list->next;
		index++;
	}
	str[index] = '\0';
	return (str);
}

char				*ft_stdin(int fd)
{
	char		buf;
	char		*str;
	int			list_len;
	t_char		*list;

	list = NULL;
	list_len = 0;
	while ((read(fd, &buf, 1)))
	{
		ft_push_back(&list, buf);
		list_len++;
	}
	str = ft_concat(&list, list_len);
	ft_list_del(&list);
	return (str);
}
