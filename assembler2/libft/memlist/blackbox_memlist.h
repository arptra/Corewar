/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blackbox_memlist.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umoff <umoff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 13:42:01 by umoff             #+#    #+#             */
/*   Updated: 2020/07/02 13:32:31 by umoff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BLACKBOX_MEMLIST_H
# define BLACKBOX_MEMLIST_H
# include "memlist.h"
# include <stdlib.h>

# define ML_MALLOC		1
# define ML_DELELEM		2
# define ML_CLEARLIST	3
# define ML_CLEARALL	4
# define ML_GIVEMEM		5
# include <stdint.h>

/*
** ml is acronym for words "memory list"
*/

typedef struct	s_ml_lists
{
	t_ml				*list;
	u_int32_t			list_num;
	struct s_ml_lists	*next;
	struct s_ml_lists	*prev;
}				t_ml_lists;

void			*ml_static_lists(void *ptr, u_int8_t rule, u_int32_t list_num);

t_ml_lists		*add_ml_list(u_int32_t list_num, t_ml_lists **cur,
															t_ml_lists **head);
t_ml			*ml_create(void *ptr);
_Bool			ml_push_front(t_ml_lists **head, t_ml *new);

void			ml_clear_all_lists(t_ml_lists *lst, t_ml_lists *head);
void			ml_delelem(t_ml **head, void *ptr);
u_int8_t		ml_clear_lst(t_ml_lists **lst, t_ml_lists **head);

t_ml			*ml_bb_givemem(t_ml_lists *lst, u_int32_t list_num);

#endif
