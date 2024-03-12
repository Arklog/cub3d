/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laliao <laliao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 17:24:56 by laliao            #+#    #+#             */
/*   Updated: 2024/03/11 17:47:54 by laliao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* function that calculate the coordinates (x, y) of the intersection of a line
with a circle of RADIUS (TILE / 25). Using a trigonometric circle with player
position as the center, and player's direction as the angle */

t_point	ft_inter_cercle_line(int direction)
{
	t_point intersection;
	
	intersection.x = TILE / 25 * cos(direction * M_PI / 180);
	intersection.y = -TILE / 25 * sin(direction * M_PI / 180);
	return (intersection); 
}

/* function that check if there is a wall in the direction of the movement. 
30 degree check around the direction on both sides */

int		ft_check_move(t_game *game, int direction)
{
	t_point	circle;
	int		angle;

	angle = direction - 30;
	circle = ft_inter_cercle_line(angle);
	while (game->map_data[(int)(game->p1.y + circle.y * 4) / TILE]
		[(int)(game->p1.x + circle.x * 4) / TILE] != WALL)
	{
		if (angle > direction + 30)
			return (1);
		angle++;
		circle = ft_inter_cercle_line(angle);
	}
	return (0);
}

/* direction shift calculates the shift in angle from the player pov angle.
So we get the direction of the movement */

void	ft_player_move(t_game *game)
{
	t_point inter;
	int		direction_shift;
	int		params;

	params = abs(game->move_x) + abs(game->move_y);
	if (game->move_y == 1 && game->move_x != 0)		//key S+A, S+D
		direction_shift = game->move_x * ((90 / params) + (180 / params));
	else if (game->move_y == 1)						//key S
		direction_shift = 180;
	else											//key W, A, D, W+A, W+D
		direction_shift = game->move_x * (90 / params);
	if (game->p1.pov + direction_shift < 0)
		direction_shift = direction_shift + 360;
	else if (game->p1.pov + direction_shift >= 360)
		direction_shift = direction_shift - 360;
	inter = ft_inter_cercle_line(game->p1.pov + direction_shift);
	if (ft_check_move(game, game->p1.pov + direction_shift))
	{
		game->p1.x = game->p1.x + inter.x;
		game->p1.y = game->p1.y + inter.y;
	}
}

void	ft_move_camera(t_game *game)
{
	if (game->rotation_x == -1)
	{
		game->p1.pov += 2;
		if (game->p1.pov >= 360)
			game->p1.pov -= 360;
	}
	else if (game->rotation_x == 1)
	{
		game->p1.pov -= 2;
		if (game->p1.pov <= 0)
			game->p1.pov = 360 + game->p1.pov;
	}
	if (game->move_x != 0 || game->move_y != 0)
		ft_player_move(game);
	ft_playerview(game);
}
