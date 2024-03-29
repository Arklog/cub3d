/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laliao <laliao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 12:29:45 by laliao            #+#    #+#             */
/*   Updated: 2024/03/14 17:29:21 by laliao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

/* function that search til it finds a wall, with diff having the distance in x
and y for the next intersection with a line of the grid (a possible wall)

current.y - 1 : for tile adjustement for horizontal intersection above
player position */

t_point	ft_find_horizontal(t_game *game, t_point a, t_point diff, double ray_a)
{
	t_point	current;

	current = a;
	while ((current.x >= 0 && current.x / TILE < game->map_lenght)
		&& (current.y >= TILE && current.y / TILE < game->map_height))
	{
		if (ray_a <= 180 && game->map_data[(int)current.y / TILE - 1]
			[(int)floor(current.x) / TILE] == WALL)
		{
			current.y -= 1;
			current.x = floor(current.x);
			return (current);
		}
		else if (ray_a > 180 && (game->map_data[(int)current.y / TILE]
				[(int)floor(current.x) / TILE] == WALL))
		{
			current.x = floor(current.x);
			return (current);
		}
		current.x = current.x + diff.x;
		current.y = current.y + diff.y;
	}
	return (game->blindspot);
}

t_point	ft_find_vertical(t_game *game, t_point a, t_point diff, double ray_a)
{
	t_point	current;

	current = a;
	while ((current.x >= TILE && current.x / TILE < game->map_lenght)
		&& (current.y >= 0 && current.y / TILE < game->map_height))
	{
		if (game->map_data[(int)floor(current.y) / TILE][(int)current.x / TILE
			- 1] == WALL && (ray_a >= 90 && ray_a <= 270))
		{
			current.x -= 1;
			current.y = floor(current.y);
			return (current);
		}
		else if ((game->map_data[(int)floor(current.y) / TILE][(int)current.x
				/ TILE] == WALL) && !(ray_a >= 90 && ray_a <= 270))
		{
			current.y = floor(current.y);
			return (current);
		}
		current.x = current.x + diff.x;
		current.y = current.y + diff.y;
	}
	return (game->blindspot);
}
