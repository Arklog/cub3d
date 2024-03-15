SRC	:=	./src/cub3d/ft_isspacestr.c \
		./src/cub3d/load_textures.c \
		./src/cub3d/load_cub3d.c \
		./src/cub3d/exit_cub3d.c \
		./src/cub3d/parse_map.c \
		./src/cub3d/get_pixel_colorf.c \
		./src/cub3d/getcol.c \
		./src/raycast/draw_wall.c \
		./src/raycast/player_move.c \
		./src/raycast/mlx.c \
		./src/raycast/raycasting.c \
		./src/raycast/raycasting_2.c \
		./src/raycast/raycasting_utils.c \
		./src/main.c \
		./src/stack.c \
		./src/map/check_map_utils.c \
		./src/map/texture_is_animated.c \
		./src/map/texture_is_texture.c \
		./src/map/texture_is_color.c \
		./src/map/load_color.c \
		./src/map/check_map.c \
		./src/map/load_animated.c \
		./src/map/load_texure.c \
		./src/map/load_map_file.c

OBJ	:= $(SRC:.c=.o)


NAME	:= cub3d
LIBFT	:= libft/libft.a
MLX	:= minilibx-linux/libmlx.a

CC	:= cc
INC	:= -Ilibft -Iminilibx-linux -Iincludes
CFLAGS	:= -Wall -Wextra -Werror -g $(INC)
LIB	:= -Llibft -lft -Lminilibx-linux -lmlx -lm -lX11 -lXext

all: $(NAME) ;

$(NAME): $(LIBFT) $(MLX) $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LIB)

$(LIBFT):
	$(MAKE) -C libft

$(MLX):
	$(MAKE) -C minilibx-linux

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean
	$(MAKE) -C .
