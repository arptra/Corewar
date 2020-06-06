//
// Created by ai on 06.06.2020.
//

#ifndef COREWAR_PARSE_H
#define COREWAR_PARSE_H

#include "libft/libft.h"

typedef struct	s_file_info
{
	char		*mh; /* MAGIC_HEADER */
	char 		*cn; /* CHAPION NAME */
	unsigned int cs; /* CHAMPION CODE SIZE */
	char 		*cc; /* CHAMPION COMMENT */
}				t_file_info;




#endif //COREWAR_PARSE_H
