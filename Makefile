#Compiler Options
#C_FLAGS =  -Wall -Wextra -Werror
C_FLAGS =  -Wall -Wextra
#Filenames
LIBFT_DIR := libft/
NAME1:= corewar
NAME2:= asm
VM:= 	\
		parse.c \
		op_codes.c \
		corewar.c \
		exec.c \
		sti.c \
		init.c \
		error_handler.c \
		utils.c 

OBJECTS_VM := $(VM:.c=.o)
#HEADER = libft/libft.h

all: $(NAME1)
$(NAME1): $(OBJECTS_VM)
	@make -C $(LIBFT_DIR)
	@gcc -g -o $(NAME1) $(VM) -L$(LIBFT_DIR) -lft
# gcc -g -o $(NAME1) $(OBJECTS_VM) -L$(LIBFT_DIR) -lft
$(OBJECTS_VM): %.o: %.c
	@gcc $(C_FLAGS) -o $@ -c $<

clean:
	@make clean -C $(LIBFT_DIR)
	@/bin/rm -f $(OBJECTS_VM)
fclean: clean
	@make fclean -C $(LIBFT_DIR)
	@/bin/rm -f $(NAME1)
	@/bin/rm -f libft.a
re: fclean all