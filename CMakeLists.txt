cmake_minimum_required(VERSION 3.14)


add_executable(vm parse.c)

add_subdirectory(libft)


target_link_libraries(vm ft)