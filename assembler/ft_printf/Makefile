# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: umoff <umoff@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/27 13:43:47 by umoff             #+#    #+#              #
#    Updated: 2020/07/02 13:32:02 by umoff            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL = /bin/sh

NAME = libftprintf.a
LIB_NAME = ./libft/libft.a

SRC_GEN = ./srcs/
SRC_FLOAT = ./srcsFloat/
HEAD_PATH = ./includes/
LIB_PATH = ../libft/

OBJS = $(SRC_FILES_GEN:.c=.o) $(SRC_FILES_FLOAT:.c=.o)

HEADERS_PRTF = $(addprefix $(HEAD_PATH),$(HEADERS_NAME))

print-%:
	@echo $*=$($*)

vpath %.c ./srcs ./srcsFloat ../libft ../libft/memlist
vpath %.h ../libft ../libft/memlist

all: $(NAME)

$(NAME): $(LIB_NAME) $(OBJS)
	@cp ../libft/libft.a ./$(NAME)
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)

$(LIB_NAME): $(PREREQUISITE_LIBFT)
	@$(MAKE) -C $(LIB_PATH)

$(OBJS): %.o: %.c $(HEADERS_PRTF)
	@gcc -c $< -I$(HEAD_PATH) -I$(LIB_PATH) $(CFLAGS) -o $@

.PHONY: clean fclean re
clean:
	@rm -f $(OBJS)
	@$(MAKE) -C $(LIB_PATH) clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIB_PATH) fclean

re: fclean all
