/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_label.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umoff <umoff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/30 13:40:37 by umoff             #+#    #+#             */
/*   Updated: 2020/07/02 14:02:43 by umoff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "assembler.h"
#include "asm_errors.h"

/*
** Функция поиска метки  
*/

_Bool	find_label(t_label **head, t_label *label_arg)
{
	_Bool l_before_al;

	l_before_al = 1;
	while (*head)
	{
		if ((*head) == label_arg)
			l_before_al = 0;
		if ((*head)->tkn->type == LABEL &&
									ft_strequ((*head)->name, label_arg->name))
			break ;
		*head = (*head)->next;
	}
	if (!*head)
		tkn_error(NO_LABEL, label_arg->tkn, 0);
	return (l_before_al);
}

/*
** Функция подсчета длины до метки  
*/

int		count_length_to_label(t_label *label, t_label *label_arg)
{
	int			length;
	t_tkn		*tkn;
	const _Bool	before = find_label(&label, label_arg);

	length = 0;
	tkn = label_arg->tkn;
	while (tkn && tkn->type != COMMAND)
		tkn = tkn->prev;
	if (before && tkn)
		tkn = tkn->prev;
	while (tkn)
	{
		if (tkn->type == COMMAND)
			length += len_command(tkn);
		if (tkn->type == LABEL && tkn->content == label)
			break ;
		tkn = (before) ? tkn->prev : tkn->next;
	}
	if (!tkn)
		go_exit("ERROR: Can't find label");
	if (before)
		length = -length;
	return (length);
}

/*
** Функция замены метки  
*/

void	replace_label(t_label *head)
{
	t_label *temp;

	if (!head)
		return ;
	temp = head;
	while (temp)
	{
		if (temp->tkn->type == ARGUMENT_LABEL)
		{
			((t_arg*)temp->tkn->content)->num =
											count_length_to_label(head, temp);
			((t_arg*)temp->tkn->content)->content = NULL;
			((t_arg*)temp->tkn->content)->type &= ~T_LAB;
			temp->tkn->type = ARGUMENT;
		}
		temp = temp->next;
	}
	ml_free_list(ML_LABEL);
}
