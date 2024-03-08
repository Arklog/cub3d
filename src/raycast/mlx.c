/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laliao <laliao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 03:19:13 by laliao            #+#    #+#             */
/*   Updated: 2024/03/08 15:03:22 by laliao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_player_move(t_game *game)
{
	if (game->move_y != 0)
		game->p1.y = game->p1.y + game->move_y * TILE / (TILE / 8);
	//else if (game->move_y == 1)
	//	game->p1.y = game->p1.y + game->move_y * TILE / (TILE / 8);
	else if (game->move_x != 0)
		game->p1.x = game->p1.x + game->move_x * TILE / (TILE / 8);
	//else
	//	game->p1.x = game->p1.x + game->move_x * TILE / (TILE / 8);
}

void	ft_move_camera(t_game *game)
{
	if (game->rotation_x == -1)
	{
		game->p1.pov += 1;
		if (game->p1.pov >= 360)
			game->p1.pov -= 360;
	}
	else if (game->rotation_x == 1)
	{
		game->p1.pov -= 1;
		if (game->p1.pov <= 0)
			game->p1.pov = 360 + game->p1.pov;
	}
	else
		ft_player_move(game);
	ft_playerview(game);
}

int	ft_key_press(int keycode, t_game *game)
{
	if (keycode == KEY_A)
		game->move_x = -1;
	else if (keycode == KEY_D)
		game->move_x = 1;
	else if (keycode == KEY_W)
		game->move_y = -1;
	else if (keycode == KEY_S)
		game->move_y = 1;
	else if (keycode == KEY_LEFT)
		game->rotation_x = -1;
	else if (keycode == KEY_RIGHT)
		game->rotation_x = 1;
	else if (keycode == ESC)
	{
		ft_exit(game);
		return (1);
	}
	return (0);
}

int	ft_key_release(int keycode, t_game *game)
{
	if (keycode == KEY_A || keycode == KEY_D)
		game->move_x = 0;
	else if (keycode == KEY_W || keycode == KEY_S)
		game->move_y = 0;
	else if (keycode == KEY_LEFT || keycode == KEY_RIGHT)
		game->rotation_x = 0;
	return (0);
}

int	ft_key_event(t_game *game)
{
	if (game->move_x || game->move_y || game->rotation_x)
		ft_move_camera(game);
	return (0);
}

int	set_window(t_game *game)
{
	game->window = mlx_new_window(game->mlx, WIN_LENGHT, WIN_HEIGHT, "Cub3d");
	if (!game->window)
	{
		//free;
		return (1);
	}
	return (0);
}
