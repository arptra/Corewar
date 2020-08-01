#C_FLAGS =  -Wall -Wextra -Werror
C_FLAGS =  -Wall -Wextra
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
		srcs/op_codes_2.c \
		srcs/op_codes_3.c \
		srcs/init.c \
		srcs/error_handler.c \
		srcs/check.c \
		srcs/free.c \
		srcs/work_with_fd.c \
		srcs/parse_player.c \
		srcs/check_args.c \
		srcs/check_args_2.c \
		srcs/visual.c \
		srcs/visual_2.c \
		srcs/print.c \
		op_codes/add.c \
		op_codes/aff.c \
		op_codes/and.c \
		op_codes/fork.c \
		op_codes/ld.c \
		op_codes/ldi.c \
		op_codes/lfork.c \
		op_codes/live.c \
		op_codes/lldi.c \
		op_codes/lld.c \
		op_codes/or.c \
		op_codes/st.c \
		op_codes/sti.c \
		op_codes/sub.c \
		op_codes/xor.c \
		op_codes/zjmp.c \
		vm_ft_printf/aux_pow_add.c \
		vm_ft_printf/ft_printf.c \
		vm_ft_printf/longdiv.c \
		vm_ft_printf/longdouble.c \
		vm_ft_printf/parser.c \
		vm_ft_printf/parser_2.c \
		vm_ft_printf/print_char.c \
		vm_ft_printf/print_eg.c \
		vm_ft_printf/print_float.c \
		vm_ft_printf/print_float_2.c \
		vm_ft_printf/print_float_3.c \
		vm_ft_printf/print_frac.c \
		vm_ft_printf/print_int.c \
		vm_ft_printf/print_int_2.c \
		vm_ft_printf/print_itoa.c \
		vm_ft_printf/print_o.c \
		vm_ft_printf/print_o_2.c \
		vm_ft_printf/print_str.c \
		vm_ft_printf/print_trash.c \
		vm_ft_printf/print_uint.c \
		vm_ft_printf/print_uint_2.c \
		vm_ft_printf/print_utf.c

OBJECTS_VM := $(VM:.c=.o)

all: $(NAME1) $(NAME2)
$(NAME1): $(OBJECTS_VM)
	@make -C $(LIBFT_DIR)
	@gcc -g -o $(NAME1) $(VM) -L$(LIBFT_DIR) -lft
$(OBJECTS_VM): %.o: %.c
	@gcc $(C_FLAGS) -o $@ -c $<
$(NAME2):
	@make -C assembler/assembler

clean:
	@make clean -C $(LIBFT_DIR)
	@/bin/rm -f $(OBJECTS_VM)
fclean: clean
	@make fclean -C assembler/assembler
	@make fclean -C $(LIBFT_DIR)
	@/bin/rm -f $(NAME1)
	@/bin/rm -f libft.a
re: fclean all