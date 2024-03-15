/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laliao <laliao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 18:08:18 by pierre            #+#    #+#             */
/*   Updated: 2024/03/15 16:28:16 by laliao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "cub3d.h"
#include "map.h"
#include "mlx.h"
#include "ft_string.h"

static void	set_pos(t_cub3d *cub)
{
	t_player	*p;
	t_map		*map;
	char		tile;

	p = &(cub->game.p1);
	map = &(cub->map);
	tile = map->map[map->starting_pos.y][map->starting_pos.x];
	if (tile == EAST)
		p->pov = 0;
	else if (tile == NORTH)
		p->pov = 90;
	else if (tile == WEST)
		p->pov = 180;
	else
		p->pov = 270;
}

static t_errors	convert_game_datas(t_cub3d *cub)
{
	t_game				*game;

	game = &(cub->game);
	game->cub3d = cub;
	game->map_data = cub->map.map;
	game->map_height = cub->map.height;
	game->map_lenght = cub->map.width;
	game->window = cub->mlx.window;
	game->mlx = cub->mlx.mlx;
	game->blindspot.x = 0;
	game->blindspot.y = 0;
	game->p1.tile_x = cub->map.starting_pos.x;
	game->p1.tile_y = cub->map.starting_pos.y;
	game->p1.x = cub->map.starting_pos.x * TILE + TILE / 2;
	game->p1.y = cub->map.starting_pos.y * TILE + TILE / 2;
	set_pos(cub);
	game->img.mlx_img = mlx_new_image(game->mlx, WIN_LENGHT, WIN_HEIGHT);
	if (!game->img.mlx_img)
		return (E_ALLOCATION_FAILURE);
	game->img.addr = mlx_get_data_addr(game->img.mlx_img,
			&game->img.bits_per_pixel, &game->img.size_line, &game->img.endian);
	return (E_NO_ERROR);
}

int	main(int argc, char **argv)
{
	t_cub3d		cub3d;
	t_game		*game_data;
	t_errors	err;

	ft_memset(&cub3d, 0, sizeof(t_cub3d));
	if (argc != 2)
		exit_cub3d(&cub3d, E_INVALID_ARGUMENTS);
	err = load_cub3d(argv[1], &cub3d);
	if (err)
		exit_cub3d(&cub3d, err);
	game_data = &(cub3d.game);
	if (convert_game_datas(&cub3d))
		exit_cub3d(&cub3d, E_ALLOCATION_FAILURE);
	ft_playerview(game_data);
	mlx_hook(game_data->window, 2, 1L << 0, ft_key_press, game_data);
	mlx_hook(game_data->window, 3, 1L << 1, ft_key_release, game_data);
	mlx_hook(game_data->window, 17, 1L << 17, ft_exit_redcross, game_data);
	mlx_loop_hook(game_data->mlx, ft_key_event, game_data);
	mlx_loop(game_data->mlx);
	exit_cub3d(&cub3d, E_NO_ERROR);
	return (0);
}
