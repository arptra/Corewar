#Compiler Options
C_FLAGS =  -Wall -Wextra  -I.
#Filenames
LIBFT_DIR := libft/
LIB := libft/libft.a
NAME :=  libftprintf.a
SRCS := ft_printf.c parser.c print_itoa.c print_int.c print_uint.c\
	print_str.c print_trash.c print_char.c print_float.c print_o.c\
	parser_2.c print_float_2.c print_int_2.c print_o_2.c print_uint_2.c\
	print_float_3.c longdiv.c longdouble.c print_utf.c\
	print_eg.c print_frac.c aux_pow_add.c
OBJECTS := $(SRCS:.c=.o)
HEADER = ft_printf.h
all: $(NAME)
$(NAME): $(LIB) $(OBJECTS)
	cp $(LIBFT_DIR)libft.a ./
	mv libft.a $(NAME)
	ar rc $(NAME) $(OBJECTS)
	ranlib $(NAME)
.FORCE:
$(LIB): .FORCE
	make -C $(LIBFT_DIR)
$(OBJECTS): %.o: %.c $(HEADER)
	gcc $(C_FLAGS) -o $@ -c $<

clean:
	make clean -C $(LIBFT_DIR)
	/bin/rm -f $(OBJECTS)
fclean: clean
	make fclean -C $(LIBFT_DIR)
	/bin/rm -f $(NAME)
	/bin/rm -f libft.a
re: fclean all

