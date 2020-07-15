cmake_minimum_required(VERSION 3.14)


add_executable(vm parse.h
        corewar.h
        init.c
        parse.c
        op_codes.c
        corewar.c
        exec.c
        error_handler.c
        utils.c
        parametrs_to_op_code.c
        check.c
        free.c
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
        op_codes/lfork.c)

add_subdirectory(libft)


target_link_libraries(vm ft)