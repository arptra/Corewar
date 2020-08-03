/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_in_tkns.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umoff <umoff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/31 13:41:15 by umoff             #+#    #+#             */
/*   Updated: 2020/07/02 14:03:15 by umoff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "assembler.h"
#include "asm_word.h"

/*
** Проверка файла на \n и конец файла
*/

void	newline_endfile_check(int fd, char *line, int ret, t_tkn *tkn)
{
	char *temp;
	char c;

	if (ret < 0 || !tkn || !tkn->prev)
		go_exit("ERROR: empty file");
	if (tkn->prev->type == COMMENT && tkn->prev->prev &&
	tkn->prev->prev->type == NEW_LINE)
		return ;
	temp = line + ft_strlen(line) - 1;
	while (temp + 1 != line)
	{
		if (!this_special(*temp, SPACES))
			break ;
		temp--;
	}
	if (temp + 1 == line)
		return ;
	c = 0;
	if (lseek(fd, -1, SEEK_CUR) == -1 || read(fd, &c, 1) != 1)
		go_exit("ERROR: cant't read file");
	if (c != '\n')
		go_exit("ERROR: No new line before end of file");
}

/*
** Функция разбивки линии на токены
*/

void	split_in_tkns_line(t_pc *pc, t_tkn **tkn, t_label **label, char *str)
{
	u_int8_t	flag;

	flag = 0;
	pc->line = str;
	pc->row++;
	pc->column = 1;
	if (check_prev_str(*tkn, 0) != NOTENDSTR)
		scroll_n(pc, skip_delimiters(pc->line, SPACES) - str);
	while (*pc->line || !flag)
	{
		add_tkn(pc, tkn, label, flag);
		if ((flag = tkn_scroll(pc, *tkn)) == TKNZE_BREAK)
			break ;
	}
	if ((*tkn)->type != NEW_LINE)
		add_tkn(pc, tkn, label, ENDLINE);
	pc->line = str;
}

/*
** Функция установки списков при запуске
*/


void	set_lists_at_start(t_tkn **tkn, t_label **label)
{
	while ((*tkn)->prev)
		*tkn = (*tkn)->prev;
	while (*label && (*label)->prev)
		*label = (*label)->prev;
}

/*
** Функция разбивки файла на токены
*/

void	split_in_tkns(int fd, t_tkn **tkn, t_label **label)
{
	t_pc		pc;
	char		*temp;
	int			ret;

	pc.row = 0;
	while ((ret = ml_get_next_line(fd, &temp, ML_GNL_LINE)) > 0)
		split_in_tkns_line(&pc, tkn, label, temp);
	if (!*tkn)
		go_exit("ERROR: File is empty");
	newline_endfile_check(fd, pc.line, ret, (*tkn));
	add_tkn(&pc, tkn, label, ENDFILE);
	set_lists_at_start(tkn, label);
}
