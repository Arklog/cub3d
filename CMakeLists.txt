cmake_minimum_required(VERSION 3.26)
project(cub3d C)

set(CMAKE_C_STANDARD 99)

include_directories(includes libft minilibx-linux)
file(GLOB_RECURSE SRC "src/*.c")

add_executable(cub3d ${SRC} src/main.c)
target_compile_options(cub3d PRIVATE -Wall -Wextra -Werror)
target_link_libraries(cub3d ft mlx X11 Xext)
target_link_directories(cub3d PRIVATE libft minilibx-linux)