/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_word.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umoff <umoff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 13:41:06 by umoff             #+#    #+#             */
/*   Updated: 2020/07/02 14:01:33 by umoff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_WORD_H
# define ASM_WORD_H

char	*skip_word(char *str, char *delims);
char	*skip_delimiters(char *str, char *delims);
_Bool	this_digit_word(char *str, char *delims);
_Bool	this_special(char c, char *special);
int		equals(char *ethalon, char *str, char *delims);


#endif
