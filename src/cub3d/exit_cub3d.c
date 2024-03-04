#include <stdlib.h>
#include <stdio.h>
#include "cub3d.h"

static const char	*g_error_msg[E_ERROR_COUNT] = {
[E_NO_ERROR] = "No error",
[E_INVALID_ARGUMENTS] = "Invalid arguments",
[E_MAP_ERROR] = "Invalid map",
[E_MLX_INIT] = "Failed to init mlx",
[E_MLX_WINDOW] = "Failed to create window",
[E_MAP_INVALID_EXTENSION] = "Invalid map extension",
[E_MAP_INVALID_DIMENSIONS] = "Invalid map dimension",
[E_MAP_INVALID_PATH] = "Invalid map path",
[E_MAP_INVALID_CHAR] = "Invalid character in map",
[E_TEXTURE_ERROR] = "Invalid texture",
[E_TEXTURE_INVALID_PATH] = "Invalid texture path",
[E_ALLOCATION_FAILURE] = "Memory allocation failure",
};

static void	free_texture(t_texture *tex, t_cub3d *cub)
{
	size_t 				i;
	t_animated_texture	*atex;

	if (tex->type == T_TEXTURE && tex->data.texture.data)
		mlx_destroy_image(cub->mlx.mlx, tex->data.texture.data);
	else if (tex->type == T_ANIMATED_TEXTURE)
	{
		i = 0;
		atex = &(tex->data.animated_texture);
		while (i < atex->count)
		{
			if (atex->textures[i].data)
				mlx_destroy_image(cub->mlx.mlx, atex->textures[i].data);
		}
	}
}

static void	free_mlx(t_cub3d *cub)
{
	int i;

	i = 0;
	while (i < 6)
		free_texture(cub->textures + i++, cub);
	if (cub->mlx.window)
		mlx_destroy_window(cub->mlx.mlx, cub->mlx.window);
	if (cub->mlx.mlx)
		mlx_destroy_display(cub->mlx.mlx);
}

void	exit_cub3d(t_cub3d *cub3d, t_errors code)
{
	if (cub3d->parser.buffer)
		free(cub3d->parser.buffer);
	free_mlx(cub3d);
	if (code)
		printf("Error\n%s\n", g_error_msg[code]);
	exit(code > 0);
}
