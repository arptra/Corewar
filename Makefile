#Compiler Options
#C_FLAGS =  -Wall -Wextra -Werror
C_FLAGS =  -Wall -Wextra
#Filenames
LIBFT_DIR := libft/
NAME1:= corewar
NAME2:= asm
VM:= 	\
		ldi.c \
		and.c \
		utils.c \
		aff.c \
		corewar.c \
		add.c \
		parse.c \
		ld.c \
		parametrs_to_op_code.c \
		zjmp.c \
		exec.c \
		op_codes.c \
		sti.c \
		init.c \
		live.c \
		error_handler.c

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