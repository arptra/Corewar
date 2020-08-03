/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_funcs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umoff <umoff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 13:44:58 by umoff             #+#    #+#             */
/*   Updated: 2020/07/02 13:26:20 by umoff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ptintf.h"

void	parsing_flags(char **format, t_prsng *tools)
{
	while (1)
	{
		if (**format == '-')
			tools->flags |= M_MINUS;
		else if (**format == '+')
			tools->flags |= M_PLUS;
		else if (**format == '#')
			tools->flags |= M_SHARP;
		else if (**format == '0')
			tools->flags |= M_ZERO;
		else if (**format == ' ')
			tools->flags |= M_SPACE;
		else if (**format == 'b')
			tools->flags |= M_B;
		else if (!is_signflag(**format))
			break ;
		(*format)++;
	}
}

void	parsing_modifiers(char **format, t_prsng *tools)
{
	if (**format == 'h' && *(*format + 1) == 'h')
		tools->mdfirs |= M_HH;
	else if (**format == 'l' && *(*format + 1) == 'l')
		tools->mdfirs |= M_LL;
	else if (**format == 'h')
		tools->mdfirs |= M_H;
	else if (**format == 'l')
		tools->mdfirs |= M_L;
	else if (**format == 'L')
		tools->mdfirs |= M_UPPER_L;
	if (*(*format + 1) == 'h' || *(*format + 1) == 'l')
		(*format) += 2;
	else
		(*format)++;
}

void	parsing_field(char **format, t_prsng *tools)
{
	long long temp;

	if (**format == '*')
	{
		if ((temp = va_arg(tools->ap, int)) < 0)
		{
			tools->flags |= M_MINUS;
			tools->field = (size_t)(-temp);
		}
		else
			tools->field = temp;
		(*format)++;
	}
	else
	{
		tools->field = ft_atoi(*format);
		while ((**format >= '0' && **format <= '9'))
			(*format)++;
	}
}

void	parsing_precision(char **format, t_prsng *tools)
{
	(*format)++;
	if (**format == '*')
	{
		tools->prec = va_arg(tools->ap, int);
		(*format)++;
	}
	else
	{
		tools->prec = ft_atoi(*format);
		while ((**format >= '0' && **format <= '9'))
			(*format)++;
	}
}

void	parsing_typeflag(char **format, t_prsng *tools)
{
	if (ft_islower(**format) || (**format != 'C' && **format != 'S'))
		tools->type = **format;
	else
	{
		tools->mdfirs |= M_L;
		tools->type = ft_tolower(**format);
	}
	(*format)++;
}
