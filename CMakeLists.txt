cmake_minimum_required(VERSION 3.15)
project(lem_in C)

set(CMAKE_C_STANDARD 99)

add_executable(lem_in main.c lem_in.h lem_atoi.c lem_split.c)

target_link_libraries(lem_in /Users/gtristan/CLionProjects/libft/libft.a)