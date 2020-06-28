cmake_minimum_required(VERSION 3.14)


add_executable(vm parse.h corewar.h init.c parse.c op_codes.c corewar.c exec.c)

add_subdirectory(libft)


target_link_libraries(vm ft)