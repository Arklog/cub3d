/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cub3d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pducloux <pducloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:44:25 by pducloux          #+#    #+#             */
/*   Updated: 2024/03/08 16:10:30 by pducloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "cub3d.h"

static const char	*g_error_msg[E_ERROR_COUNT] = {
[E_NO_ERROR] = "No error",
[E_INVALID_ARGUMENTS] = "Invalid arguments",
[E_MLX_INIT] = "Failed to init mlx",
[E_MLX_WINDOW] = "Failed to create window",
[E_MAP_ERROR] = "Invalid map",
[E_MAP_FILE_ERROR] = "Invalid map path",
[E_MAP_INVALID_EXTENSION] = "Invalid map extension",
[E_MAP_INVALID_DIMENSIONS] = "Invalid map dimension",
[E_MAP_INVALID_WALL] = "Map must be surrounded by walls",
[E_MAP_INVALID_CHAR] = "Invalid character in map",
[E_MAP_NO_STARTPOS] = "Map is missing a starting player position",
[E_MAP_MULTIPLE_STARTPOS] = "Map has multiple starting player positions",
[E_TEXTURE_ERROR] = "Invalid texture",
[E_TEXTURE_INVALID_PATH] = "Invalid texture path",
[E_TEXTURE_MISSING] = "Missing texture",
[E_TEXTURE_INVALID_INDEX] = "Invalid texture index (expected NO,SO,WE,EA,F,C)",
[E_ALLOCATION_FAILURE] = "Memory allocation failure",
};

static void	free_texture(t_texture *tex, t_cub3d *cub)
{
	size_t				i;
	t_animated_texture	*atex;

	if (tex->type == T_TEXTURE && tex->u_data.texture.data)
		mlx_destroy_image(cub->mlx.mlx, tex->u_data.texture.data);
	else if (tex->type == T_ANIMATED_TEXTURE)
	{
		i = 0;
		atex = &(tex->u_data.animated_texture);
		while (i < atex->count)
		{
			if (atex->textures[i].data)
				mlx_destroy_image(cub->mlx.mlx, atex->textures[i].data);
		}
	}
}

static void	free_mlx(t_cub3d *cub)
{
	int	i;

	i = 0;
	while (i < 6)
		free_texture(cub->textures + i++, cub);
	if (cub->game.img.mlx_img)
		mlx_destroy_image(cub->mlx.mlx, cub->game.img.mlx_img);
	if (cub->mlx.window)
		mlx_destroy_window(cub->mlx.mlx, cub->mlx.window);
	if (cub->mlx.mlx)
	{
		mlx_destroy_display(cub->mlx.mlx);
		free(cub->mlx.mlx);
	}
}

static void	free_parser(t_parser *parser)
{
	if (!parser)
		return ;
	if (parser->buffer)
		free(parser->buffer);
	if (parser->lines)
		free(parser->lines);
}

static void	free_map(t_map *map)
{
	if (!map)
		return ;
	if (map->buffer)
		free(map->buffer);
	if (map->map)
		free(map->map);
}

void	exit_cub3d(t_cub3d *cub3d, t_errors code)
{
	free_mlx(cub3d);
	free_parser(&(cub3d->parser));
	free_map(&(cub3d->map));
	if (code)
		printf("Error\n%s\n", g_error_msg[code]);
	exit(code > 0);
}
