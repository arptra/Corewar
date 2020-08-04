/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_errors.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbookair <macbookair@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 13:38:14 by umoff             #+#    #+#             */
/*   Updated: 2020/08/04 12:43:40 by macbookair       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_ERRORS_H
# define ASM_ERRORS_H

/*
** Ошибки
*/

# define NAME_MISSING		"ERROR: The name is missing in the champion file"

# define CMNT_MISSING		"ERROR: The comment is missing in the champion file"

# define NL_MISSING			"ERROR: No new line"

# define CMD_MISS	        "ERROR: Need a command token before the argument"

# define EXTR_SPRTR	        "ERROR: Arguments not separated from a command"

# define SPRTR_MISS	        "ERROR: Arguments must be separated"

# define NAME_CMT	        "ERROR: Invalid name or comment of the сhampion"

# define DOUBLE_COMMENT		"ERROR: The champion can have a double comment"

# define DOUBLE_NAME		"ERROR: The champion can have a double name"

# define WRONG_SEPARATOR	"ERROR: Arguments are separated incorrectly"

# define LONG_NAME			"ERROR: The сhampion's name is too long"

# define LONG_CMNT			"ERROR: The сhampion's comment is too long"

# define ERR_ARGS			"ERROR: The command has by incorrect arguments"

# define INVALID_STR_PLACE	"ERROR: The token string in the wrong place"

# define INVALID_STR		"ERROR: Invalid string token"

# define NOCODE				"ERROR: The program has no code after the string"

# define NO_LABEL			"ERROR: The label does not exist"

# define INVALID_CMD		"ERROR: The command is invalid"

# define TREG_INVALID_NUM	"ERROR: The argument T_REG has an invalid number"

/*
** Предупреждения
*/

# define WRNNG_TREG_INVALID_NUM	"WARNING: Argument T_REG has incorrect number"

#endif
