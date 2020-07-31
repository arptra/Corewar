cmake_minimum_required(VERSION 3.14)

project(libft_printf)

add_library(ft_printf STATIC ft_printf.h
        ft_printf.c parser.c print_itoa.c print_int.c print_uint.c
        print_str.c print_trash.c print_char.c print_float.c print_o.c
        parser_2.c print_float_2.c print_int_2.c print_o_2.c print_uint_2.c
        print_float_3.c longdiv.c longdouble.c print_utf.c
        print_eg.c print_frac.c aux_pow_add.c)

add_subdirectory(libft)

target_link_libraries(ft_printf ft)