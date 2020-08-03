# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: umoff <umoff@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/27 13:41:34 by umoff             #+#    #+#              #
#    Updated: 2020/07/02 13:49:05 by umoff            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL = /bin/sh

NAME = libft.a

SRC_ML_DIR = ./memlist/

OBJECTS = $(SRCS_LIBFT:.c=.o)
OBJECTS_ML = $(SRC_ML:.c=.o)

HEADERS = get_next_line.h libft.h memlist.h
HEADERS_ML = $(SRC_ML_DIR)blackbox_memlist.h
INCLUDE = ./

vpath %.c ./memlist

all: $(NAME)

$(NAME): $(OBJECTS) $(OBJECTS_ML)
	@ar rc $(NAME) $(OBJECTS) $(OBJECTS_ML)
	@ranlib $(NAME)

$(OBJECTS): %.o: %.c $(HEADERS)
	@gcc -c $< -I$(INCLUDE) $(CFLAGS) -o $@

$(OBJECTS_ML): %.o: %.c $(HEADERS_ML) libft.h
	@gcc -c $< -I$(SRC_ML_DIR) -I$(INCLUDE) $(CFLAGS) -o $@

.PHONY: clean fclean re
clean:
	@rm -f $(OBJECTS)
	@rm -f $(OBJECTS_ML)

fclean: clean
	@rm -f $(NAME)

re: fclean all
