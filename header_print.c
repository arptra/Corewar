/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umoff <umoff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 14:17:24 by umoff             #+#    #+#             */
/*   Updated: 2020/07/02 14:02:07 by umoff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "options.h"

/*
**  Функция печати в обратном порядке 
*/

void	print_reverse(int fd, u_int8_t byte, u_int32_t *num)
{
	while (byte--)
		write(fd, &((u_int8_t*)num)[byte], 1);
}

/*
**  Функция печати заголовка 
*/

void	header_print(int fd, t_header *header)
{
	int nullo;

	print_reverse(fd, 4, &header->magic);
	write(fd, &header->prog_name, PROG_NAME_LENGTH);
	nullo = 0;
	write(fd, &nullo, 4);
	print_reverse(fd, 4, &header->prog_size);
	write(fd, &header->comment, COMMENT_LENGTH);
}
