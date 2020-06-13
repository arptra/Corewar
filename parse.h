//
// Created by ai on 06.06.2020.
//

#ifndef COREWAR_PARSE_H
#define COREWAR_PARSE_H

#include "libft/libft.h"
#include "op.h"

typedef struct	s_file_info
{
	char		*mh; /* MAGIC_HEADER */
	char 		*cn; /* CHAMPION NAME */
	unsigned int cs; /* CHAMPION CODE SIZE */
	char 		*cc; /* CHAMPION COMMENT */
	int			cnum;	/* CHAMPION NUMBER */
	t_file_info	*next;	/* next champion */
}				t_file_info;


#endif //COREWAR_PARSE_H
