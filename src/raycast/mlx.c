/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laliao <laliao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 03:19:13 by laliao            #+#    #+#             */
/*   Updated: 2024/03/11 17:25:28 by laliao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_key_press(int keycode, t_game *game)
{
	if (keycode == KEY_A)
		game->move_x = 1;
	else if (keycode == KEY_D)
		game->move_x = -1;
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
		exit_cub3d(game->cub3d, E_NO_ERROR);
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
