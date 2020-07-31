/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgerda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 16:21:51 by bgerda            #+#    #+#             */
/*   Updated: 2020/01/18 16:31:16 by bgerda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		codepoint_len(const uint32_t cp)
{
	int		len;
	t_utf	**u;
	t_utf	*utf[5];

	utf[0] = &(t_utf) {0b00111111, 0b10000000, 0, 0, 6};
	utf[1] = &(t_utf) {0b01111111, 0b00000000, 0000, 0177, 7};
	utf[2] = &(t_utf) {0b00011111, 0b11000000, 0200, 03777, 5};
	utf[3] = &(t_utf) {0b00001111, 0b11100000, 04000, 0177777, 4};
	utf[4] = &(t_utf) {0b00000111, 0b11110000, 0200000, 04177777, 3};
	u = utf;
	len = 0;
	while (*u)
	{
		if ((cp >= (*u)->beg) && (cp <= (*u)->end))
			break ;
		++len;
		u++;
	}
	return (len);
}

char	*to_utf8(const uint32_t cp)
{
	int			i;
	static char	ret[5];
	int			bytes;
	int			shift;
	t_utf		*utf[5];

	utf[0] = &(t_utf) {0b00111111, 0b10000000, 0, 0, 6};
	utf[1] = &(t_utf) {0b01111111, 0b00000000, 0000, 0177, 7};
	utf[2] = &(t_utf) {0b00011111, 0b11000000, 0200, 03777, 5};
	utf[3] = &(t_utf) {0b00001111, 0b11100000, 04000, 0177777, 4};
	utf[4] = &(t_utf) {0b00000111, 0b11110000, 0200000, 04177777, 3};
	bytes = codepoint_len(cp);
	shift = utf[0]->bits_stored * (bytes - 1);
	ret[0] = (cp >> shift & utf[bytes]->mask) | utf[bytes]->lead;
	shift -= utf[0]->bits_stored;
	i = 1;
	while (i < bytes)
	{
		ret[i] = (cp >> shift & utf[0]->mask) | utf[0]->lead;
		shift -= utf[0]->bits_stored;
		i++;
	}
	ret[bytes] = '\0';
	return (ret);
}

void	uputchar_fd(char c, int fd, int r)
{
	if (ft_isprint(c) == 0 && r == 1)
		ft_putstr(to_utf8(0x2400 + c));
	else
		write(fd, &c, 1);
}
