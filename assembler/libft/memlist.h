/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memlist.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umoff <umoff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 13:41:42 by umoff             #+#    #+#             */
/*   Updated: 2020/07/02 13:49:08 by umoff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMLIST_H
# define MEMLIST_H
# include <stdlib.h>

typedef struct	s_ml
{
	void		*data;
	struct s_ml	*next;
	struct s_ml	*prev;
}				t_ml;

/*
** ml is acronym for words "memory list"
*/

void			*ml_malloc(size_t size, u_int32_t list_num);
void			ml_free(void *ptr, u_int32_t list_num);
void			ml_free_list(u_int32_t list_num);
void			ml_free_all(void);
t_ml			*ml_givemem(u_int32_t list_num);

/*
**  functions wich using memory list
*/

int				ml_get_next_line(const int fd, char **line, u_int32_t lst_num);

void			*ml_memalloc(size_t size, u_int32_t lst_num);

char			*ml_strdup(const char *src, u_int32_t lst_num);
char			*ml_strndup(const char *s1, size_t n, u_int32_t lst_num);

char			*ml_strnew(size_t size, u_int32_t lst_num);
char			*ml_strjoin(const char *s1, const char *s2, u_int32_t lst_num);
char			*ml_strjoinre(char **s1, char const *s2, u_int32_t lst_num);
char			*ml_strsub(const char *s, unsigned int start, size_t len,
														u_int32_t lst_num);
char			*ml_strtrim(const char *s, u_int32_t lst_num);
char			**ml_strsplit(const char *s, char c, u_int32_t lst_num);

char			*ml_strmap(const char *s, char (*f)(char), u_int32_t lst_num);
char			*ml_strmapi(const char *s, char (*f)(unsigned int, char),
							u_int32_t lst_num);
char			*ml_itoa(int n, u_int32_t lst_num);

#endif
