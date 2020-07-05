cmake_minimum_required(VERSION 3.14)


add_executable(vm parse.h corewar.h init.c parse.c op_codes.c corewar.c exec.c error_handler.c utils.c sti.c ld.c parametrs_to_op_code.c live.c)

add_subdirectory(libft)


target_link_libraries(vm ft)