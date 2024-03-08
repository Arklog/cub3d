/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pducloux <pducloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 18:08:18 by pierre            #+#    #+#             */
/*   Updated: 2024/03/08 16:03:25 by pducloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "cub3d.h"
#include "map.h"
#include "mlx.h"
#include "ft_string.h"

static void	convert_game_datas(t_cub3d *cub)
{
	t_game				*game;
	t_img				*img;
	t_texture_simple	*s;

	game = &(cub->game);
	game->cub3d = cub;
	game->map_data = cub->map.map;
	game->map_height = cub->map.height;
	game->map_lenght = cub->map.width;
	game->window = cub->mlx.window;
	game->mlx = cub->mlx.mlx;
	img = &(game->img);
	s = &(cub->textures[TEXTURE_NORTH].u_data.texture);
	// img->addr = s->raw;
	// img->bits_per_pixel = s->bpp;
	// img->endian = s->endian;
	// img->mlx_img = s->data;
	// img->size_line = s->line_size;
}

int main(int argc, char **argv) {
	t_cub3d	cub3d;
	t_game	*game_data;
	t_errors err;

	ft_memset(&cub3d, 0, sizeof(t_cub3d));
	if (argc != 2)
		exit_cub3d(&cub3d, E_INVALID_ARGUMENTS);
	err = load_cub3d(argv[1], &cub3d);
	if (err)
		exit_cub3d(&cub3d, err);
	game_data = &(cub3d.game);
	convert_game_datas(&cub3d);
	ft_playerview(game_data);
	mlx_hook(game_data->window, 2, 1L<<0, ft_key_press, game_data);
	mlx_hook(game_data->window, 3, 1L<<1, ft_key_release, game_data);
	// mlx_hook(game_data->window, 17, 1L << 17, ft_exit_redcross, game_data);
	mlx_loop_hook(game_data->mlx, ft_key_event, game_data);
	mlx_loop(game_data->mlx);
	exit_cub3d(&cub3d, E_NO_ERROR);
	return (0);
}
