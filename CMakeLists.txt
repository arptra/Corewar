cmake_minimum_required(VERSION 3.14)


add_executable(vm
        srcs/corewar.c
        srcs/init.c
        srcs/parse.c
        srcs/op_codes.c
        srcs/op_codes_2.c
        srcs/op_codes_3.c
        srcs/parse.c
        srcs/exec.c
        srcs/error_handler.c
        srcs/utils.c
        srcs/parametrs_to_op_code.c
        srcs/check.c
        srcs/free.c
        srcs/work_with_fd.c
        srcs/parse_player.c
        srcs/check_args.c
        srcs/check_args_2.c
        srcs/print.c
        srcs/visual.c
        srcs/visual_2.c

        op_codes/sti.c
        op_codes/ld.c
        op_codes/live.c
        op_codes/zjmp.c
        op_codes/add.c
        op_codes/aff.c
        op_codes/and.c
        op_codes/ldi.c
        op_codes/lld.c
        op_codes/lldi.c
        op_codes/or.c
        op_codes/sub.c
        op_codes/xor.c
        op_codes/st.c
        op_codes/fork.c
        op_codes/lfork.c )

add_subdirectory(libft)

add_subdirectory(ft_printf)

include_directories(incl)

target_link_libraries(vm ft ft_printf)