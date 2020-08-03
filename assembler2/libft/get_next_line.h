/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umoff <umoff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 14:11:54 by umoff             #+#    #+#             */
/*   Updated: 2020/07/02 13:48:51 by umoff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>
# include "libft.h"

# define BF_SZ_GNL 64

typedef struct	s_gnl
{
	int				fd_;
	char			*str;
	char			*lb;
	struct s_gnl	*next;
}				t_gnl;

t_gnl			*new_node(const int fd);
int				find_fd(t_gnl **lst, const int fd);
int				ad_fd(t_gnl **lst, t_gnl *new);
int				free_node(t_gnl **lst);

#endif
