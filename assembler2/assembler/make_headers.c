/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_headers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umoff <umoff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/30 13:40:30 by umoff             #+#    #+#             */
/*   Updated: 2020/07/02 14:02:19 by umoff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

/*
** Функция подсчета размера программы 
*/

unsigned int	calc_progsize(t_tkn *tkn)
{
	t_tkn			*cp_tok;
	unsigned int	weight;

	weight = 0;
	cp_tok = tkn;
	while (tkn->next != NULL)
	{
		if (tkn->type == COMMAND)
			weight +=len_command(tkn);
		tkn = tkn->next;
	}
	tkn = cp_tok;
	return (weight);
}

/*
** Функция создания заголовков (список)
*/

void			make_headers(t_header *header, t_tkn *tkn)
{
	ft_bzero(header->comment, COMMENT_LENGTH);
	ft_bzero(header->prog_name, PROG_NAME_LENGTH);
	(header)->magic = COREWAR_EXEC_MAGIC;
	tkn_strcat(header->prog_name, find_tkn(tkn, NAME)->next,
			PROG_NAME_LENGTH);
	tkn_strcat(header->comment, find_tkn(tkn, COMMENT_PROG)->next,
				COMMENT_LENGTH);
	(header)->prog_size = calc_progsize(tkn);
}
