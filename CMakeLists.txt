cmake_minimum_required(VERSION 3.21)
project(cub3d C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(includes libft minilibx-linux)
file(GLOB_RECURSE SRC "src/cub3d/*.c" "src/map/*.c" "src/raycast/*.c" "src/stack.c")

add_executable(cub3d ${SRC} src/main.c)
target_compile_options(cub3d PRIVATE -Wall -Wextra -Werror -DLITTLE_ENDIAN)
target_link_libraries(cub3d ft mlx X11 Xext m)
target_link_directories(cub3d PRIVATE libft minilibx-linux)
