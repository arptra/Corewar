#Compiler Options
#C_FLAGS =  -Wall -Wextra -Werror
C_FLAGS =  -Wall -Wextra
#Filenames
LIBFT_DIR := libft/
NAME1:= corewar
NAME2:= asm
VM:= 	\
		srcs/utils.c \
		srcs/corewar.c \
		srcs/parse.c \
		srcs/parametrs_to_op_code.c \
		srcs/exec.c \
		srcs/op_codes.c \
		srcs/init.c \
		srcs/error_handler.c \
		srcs/check.c \
		srcs/free.c \
		srcs/work-with-fd.c \
		srcs/parse-player.c \
		op_codes/ld.c \
		op_codes/aff.c \
		op_codes/add.c \
		op_codes/zjmp.c \
		op_codes/sti.c \
		op_codes/live.c \
		op_codes/lldi.c \
		op_codes/lld.c \
		op_codes/or.c \
		op_codes/xor.c \
		op_codes/sub.c \
		op_codes/st.c \
		op_codes/fork.c \
		op_codes/ldi.c \
		op_codes/and.c \
		op_codes/lfork.c 		

OBJECTS_VM := $(VM:.c=.o)
#HEADER = libft/libft.h

all: $(NAME1) $(NAME2)
$(NAME1): $(OBJECTS_VM)
	@make -C $(LIBFT_DIR)
	@gcc -g -o $(NAME1) $(VM) -L$(LIBFT_DIR) -lft
# gcc -g -o $(NAME1) $(OBJECTS_VM) -L$(LIBFT_DIR) -lft
$(NAME2):
	@make -C assembler/assembler
$(OBJECTS_VM): %.o: %.c
	@gcc $(C_FLAGS) -o $@ -c $<

clean:
	@make clean -C $(LIBFT_DIR)
	@/bin/rm -f $(OBJECTS_VM)
fclean: clean
	@make fclean -C assembler/assembler
	@make fclean -C $(LIBFT_DIR)
	@/bin/rm -f $(NAME1)
	@/bin/rm -f libft.a
re: fclean all