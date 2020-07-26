cmake_minimum_required(VERSION 3.14)


add_executable(vm

        srcs/init.c
        srcs/parse.c
        srcs/op_codes.c
        srcs/corewar.c
        srcs/exec.c
        srcs/error_handler.c
        srcs/utils.c
        srcs/parametrs_to_op_code.c
        srcs/check.c
        srcs/free.c
        srcs/debug_tools.c
        srcs/work-with-fd.c
        srcs/parse-player.c
        srcs/check_args.c

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
        op_codes/lfork.c srcs/visual.c)

add_subdirectory(libft)

include_directories(incl)

target_link_libraries(vm ft)